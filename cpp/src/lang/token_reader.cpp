/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 * Licensed under the MIT license. See LICENSE file in the project root for full license information.
 * @file token_reader.cpp
 * @brief Defines the token_reader class and related functions.
 */
#include <token_reader.hpp>
#include <sstream>
#include <cmath>
#include <message_utility.hpp>
#include <float_utility.hpp>

using namespace opendraft::lang;

token_reader::token_reader(
    std::istream& inner,
    const source_reference& start_source,
    std::function<void(const message&)> message_callback)
    : _inner(inner),
      _start_source(start_source),
      _line(start_source.line()),
      _column(start_source.column()),
      _peeked_token(nullptr),
      _message_callback(message_callback)
{
}

/**
 * @brief Peeks at the next token in the stream without consuming it.
 * @return A shared pointer to the next token in the stream.
 */
std::shared_ptr<token> token_reader::peek()
{
    if (_peeked_token)
    {
        return _peeked_token;
    }

    _peeked_token = inner_read();
    return _peeked_token;
}

/**
 * @brief Reads the next token from the stream and consumes it.
 * @return A shared pointer to the next token in the stream.
 */
std::shared_ptr<token> token_reader::read()
{
    auto token = peek();
    _peeked_token = nullptr;
    return token;
}

bool token_reader::is_whitespace(int ch)
{
    return ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r';
}

bool token_reader::is_identifier_start(int ch)
{
    return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || ch == '_';
}

bool token_reader::is_identifier_part(int ch)
{
    return is_identifier_start(ch) || is_digit(ch);
}

bool token_reader::is_digit(int ch)
{
    return ch >= '0' && ch <= '9';
}

bool token_reader::is_unit_start(int ch)
{
    // handle degree symbol '°' (\xC2\xB0 in UTF-8), and
    // handle rad symbol '㎭' (\xE3\x8E\xAD in UTF-8) by
    // proceeding if the first byte is the start of either, as the start of a unit
    // specifier is the only valid place for multi-byte UTF-8 characters outside of a string literal.
    return is_identifier_start(ch) ||
        ch == '\'' || ch == '"' || ch == 0xc2 || ch == 0xe3;
}

bool token_reader::is_unit_part(int ch)
{
    return is_identifier_part(ch) || ch == 0xb0 || ch == 0x8e || ch == 0xad;
}

int token_reader::get_radix(int ch)
{
    switch (ch)
    {
    case 'b':
    case 'B':
        return 2;
    case 'o':
    case 'O':
        return 8;
    case 'x':
    case 'X':
        return 16;
    default:
        return 10;
    }
}

int token_reader::get_digit(int ch, int radix)
{
    if (radix <= 10)
    {
        if (ch >= '0' && ch < '0' + radix)
        {
            return ch - '0';
        }
    }
    else
    {
        if (ch >= '0' && ch <= '9')
        {
            return ch - '0';
        }
        else if (ch >= 'a' && ch < 'a' + radix - 10)
        {
            return 10 + (ch - 'a');
        }
        else if (ch >= 'A' && ch < 'A' + radix - 10)
        {
            return 10 + (ch - 'A');
        }
    }

    return -1; // not a valid digit for the given radix
}

std::shared_ptr<token> token_reader::inner_read()
{
    skip_whitespace();

    int ch = _inner.peek();
    if (ch <= 0)
    {
        return nullptr;
    }

    if (is_identifier_start(ch))
    {
        return read_keyword_or_identifier();
    }
    else if (is_digit(ch))
    {
        return read_numeric_literal();
    }
    else if (ch == '"')
    {
        return read_string_literal();
    }
    else if (ch == '/')
    {
        source_reference start_source = current_source();
        read_char();
        ch = _inner.peek();
        if (ch == '/' || ch == '*')
        {
            return read_comment(start_source);
        }
        else
        {
            return std::make_shared<symbol_token>(start_source, symbol::SYMBOL_SLASH);
        }
    }
    else if (ch == '.')
    {
        source_reference start_source = current_source();
        read_char();
        ch = _inner.peek();
        if (is_digit(ch))
        {
            return read_decimal_literal(start_source, 0);
        }
        else
        {
            return std::make_shared<symbol_token>(start_source, symbol::SYMBOL_DOT);
        }
    }
    else
    {
        return read_symbol();
    }
}

std::shared_ptr<token> token_reader::read_keyword_or_identifier()
{
    source_reference start_source = current_source();
    std::ostringstream ss;
    int ch = read_char();
    ss << static_cast<char>(ch);
    ch = _inner.peek();
    while (is_identifier_part(ch))
    {
        ch = read_char();
        ss << static_cast<char>(ch);
        ch = _inner.peek();
    }

    std::string name = ss.str();
    source_reference source = source_reference(
        start_source.path(),
        start_source.line(),
        start_source.column(),
        _line,
        _column);
    keyword kw = keyword_from_string(name);
    if (kw != keyword::KEYWORD_UNDEFINED)
    {
        return std::make_shared<keyword_token>(source, kw);
    }
    else
    {
        return std::make_shared<identifier_token>(source, name);
    }
}

std::shared_ptr<token> token_reader::read_symbol()
{
    source_reference start_source = current_source();
    source_reference end_source = current_source();
    int ch = read_char();
    symbol sym;
    switch (ch)
    {
    case '+':
        sym = symbol::SYMBOL_PLUS;
        break;
    case '-':
        sym = symbol::SYMBOL_MINUS;
        break;
    case '*':
        sym = symbol::SYMBOL_STAR;
        break;
    case '/':
        sym = symbol::SYMBOL_SLASH;
        break;
    case '%':
        sym = symbol::SYMBOL_PERCENT;
        break;
    case '=':
        {
            sym = symbol::SYMBOL_ASSIGN;
            ch = _inner.peek();
            if (ch == '=')
            {
                end_source = current_source();
                read_char();
                sym = symbol::SYMBOL_EQUALS;
            }
        }

        break;
    case '<':
        {
            sym = symbol::SYMBOL_LESS_THAN;
            ch = _inner.peek();
            if (ch == '=')
            {
                end_source = current_source();
                read_char();
                sym = symbol::SYMBOL_LESS_THAN_EQUALS;
            }
            else if (ch == '<')
            {
                end_source = current_source();
                read_char();
                sym = symbol::SYMBOL_LEFT_SHIFT;
            }
        }

        break;
    case '>':
        {
            sym = symbol::SYMBOL_GREATER_THAN;
            ch = _inner.peek();
            if (ch == '=')
            {
                end_source = current_source();
                read_char();
                sym = symbol::SYMBOL_GREATER_THAN_EQUALS;
            }
            else if (ch == '>')
            {
                end_source = current_source();
                read_char();
                sym = symbol::SYMBOL_RIGHT_SHIFT;
            }
        }

        break;
    case '!':
        {
            sym = symbol::SYMBOL_BANG;
            ch = _inner.peek();
            if (ch == '=')
            {
                end_source = current_source();
                read_char();
                sym = symbol::SYMBOL_NOT_EQUALS;
            }
        }

        break;
    case '&':
        {
            sym = symbol::SYMBOL_AMPERSAND;
            ch = _inner.peek();
            if (ch == '&')
            {
                end_source = current_source();
                read_char();
                sym = symbol::SYMBOL_AND;
            }
        }

        break;
    case '|':
        {
            sym = symbol::SYMBOL_PIPE;
            ch = _inner.peek();
            if (ch == '|')
            {
                end_source = current_source();
                read_char();
                sym = symbol::SYMBOL_OR;
            }
        }

        break;
    case '~':
        sym = symbol::SYMBOL_TILDE;
        break;
    case '?':
        {
            sym = symbol::SYMBOL_QUESTION;
            ch = _inner.peek();
            if (ch == '?')
            {
                end_source = current_source();
                read_char();
                sym = symbol::SYMBOL_DOUBLE_QUESTION;
            }
        }

        break;
    case ':':
        sym = symbol::SYMBOL_COLON;
        break;
    case ';':
        sym = symbol::SYMBOL_SEMICOLON;
        break;
    case ',':
        sym = symbol::SYMBOL_COMMA;
        break;
    case '.':
        {
            sym = symbol::SYMBOL_DOT;
            ch = _inner.peek();
            if (ch == '.')
            {
                end_source = current_source();
                read_char();
                sym = symbol::SYMBOL_DOTDOT;
            }
        }
        
        break;
    case '(':
        sym = symbol::SYMBOL_LEFT_PAREN;
        break;
    case ')':
        sym = symbol::SYMBOL_RIGHT_PAREN;
        break;
    case '{':
        sym = symbol::SYMBOL_LEFT_BRACE;
        break;
    case '}':
        sym = symbol::SYMBOL_RIGHT_BRACE;
        break;
    case '[':
        sym = symbol::SYMBOL_LEFT_BRACKET;
        break;
    case ']':
        sym = symbol::SYMBOL_RIGHT_BRACKET;
        break;
    default:
        sym = symbol::SYMBOL_UNDEFINED;
        break;
    }

    source_reference source = source_reference(
        start_source.path(),
        start_source.line(),
        start_source.column(),
        end_source.line(),
        end_source.column());
    return std::make_shared<symbol_token>(source, sym);
}

std::shared_ptr<token> token_reader::read_numeric_literal()
{
    source_reference start_source = current_source();
    long int_part = 0;
    int ch = _inner.peek();
    int radix = 10;
    if (ch == '0')
    {
        read_char();
        ch = _inner.peek();
        radix = get_radix(ch);
        if (radix != 10)
        {
            read_char();
            ch = _inner.peek();
            if (get_digit(ch, radix) < 0)
            {
                _message_callback(message_utility::invalid_number_after_radix(
                    current_source()));
                return nullptr;
            }
        }
    }

    int digit = get_digit(ch, radix);
    while (digit >= 0)
    {
        read_char();
        int_part = int_part * radix + digit;
        ch = _inner.peek();
        digit = get_digit(ch, radix);
    }

    int exponent = 0;
    bool has_exponent = false;

    if (radix == 10)
    {
        if (ch == '.')
        {
            read_char();
            return read_decimal_literal(start_source, int_part);
        }

        if (ch == 'e' || ch == 'E')
        {
            read_char();
            has_exponent = true;
            if (!try_read_exponent_part(/*out*/ exponent))
            {
                return nullptr; // error already logged.
            }
        }
    }

    std::string unit;
    ch = _inner.peek();
    if (is_unit_start(ch))
    {
        if (!read_unit(/*out*/ unit))
        {
            return nullptr; // error already logged.
        }
    }

    source_reference source = source_reference(
        start_source.path(),
        start_source.line(),
        start_source.column(),
        _line,
        _column);
    if (has_exponent)
    {
        double result = int_part * std::pow(10.0, exponent);
        return std::make_shared<numeric_literal_token>(source, result, unit);
    }
    else
    {
        return std::make_shared<numeric_literal_token>(source, int_part, unit);
    }
}

bool token_reader::read_unit(/*out*/std::string& unit)
{
    std::ostringstream ss;
    int ch = read_char();
    bool underscore_start = ch == '_';
    if (underscore_start)
    {
        ch = _inner.peek();
        if (!is_unit_start(ch))
        {
            _message_callback(message_utility::invalid_unit_specifier(
                current_source(),
                ch > 0 ? std::string(1, static_cast<char>(ch)) : ""));
            return false; // error.
        }

        read_char();
    }

    ss << static_cast<char>(ch);
    ch = _inner.peek();
    while (is_unit_part(ch))
    {
        read_char();
        ss << static_cast<char>(ch);
        ch = _inner.peek();
    }

    // The 1st underscore is a delimiter and is removed from the result.
    unit = ss.str();

    if (unit.empty())
    {
        _message_callback(message_utility::invalid_unit_specifier(
            current_source(),
            unit));
        return false;
    }

    // reject multi-byte sequences outside the specific allowed starting chars.
    auto unit_validate_start = unit.cbegin();
    if (unit.starts_with("°"))
    {
        unit_validate_start += 2; // skip the degree symbol
    }
    else if (unit.starts_with("㎭"))
    {
        unit_validate_start += 3; // skip the rad symbol
    }

    for (auto it = unit_validate_start; it != unit.cend(); ++it)
    {
        unsigned char c = static_cast<unsigned char>(*it);
        if (c >= 0x80)
        {
            _message_callback(message_utility::invalid_unit_specifier(
                current_source(),
                unit));
            return false;
        }
    }

    return true;
}

std::shared_ptr<token> token_reader::read_decimal_literal(
    const source_reference& start_source,
    long int_part)
{
    // the decimal point has already been read.
    long frac_part = 0;
    int divisor_exponent = 0;
    int ch = _inner.peek();
    while (is_digit(ch))
    {
        read_char();
        frac_part *= 10;
        frac_part += (ch - '0');
        --divisor_exponent;
        ch = _inner.peek();
    }

    int exponent = 0;
    if (ch == 'e' || ch == 'E')
    {
        read_char();
        if (!try_read_exponent_part(/*out*/ exponent))
        {
            return nullptr; // error already logged.
        }
    }

    double value = float_utility::compose(
        int_part,
        frac_part,
        divisor_exponent,
        exponent);

    std::string unit;
    ch = _inner.peek();
    if (is_unit_start(ch))
    {
        if (!read_unit(/*out*/ unit))
        {
            return nullptr; // error already logged.
        }
    }

    source_reference source = source_reference(
        start_source.path(),
        start_source.line(),
        start_source.column(),
        _line,
        _column);
    return std::make_shared<numeric_literal_token>(source, value, unit);
}

bool token_reader::try_read_exponent_part(/*out*/ int& exponent)
{
    // 'e' or 'E' has already been read.
    exponent = 0;
    int ch = _inner.peek();
    bool is_negative = false;
    if (ch == '+' || ch == '-')
    {
        read_char();
        is_negative = (ch == '-');
        ch = _inner.peek();
    }

    if (!is_digit(ch))
    {
        _message_callback(message_utility::expected_decimal_exponent(
            current_source()));
        return false;
    }

    exponent = 0;
    while (is_digit(ch))
    {
        read_char();
        exponent = exponent * 10 + (ch - '0');
        ch = _inner.peek();
    }

    if (is_negative)
    {
        exponent = -exponent;
    }

    return true;
}

std::shared_ptr<token> token_reader::read_string_literal()
{
    source_reference start_source = current_source();
    std::ostringstream ss;
    read_char(); // consume the opening quote
    int ch = _inner.peek();
    while (ch > 0 && ch != '"' && ch != '\n')
    {
        read_char();
        if (ch == '\\')
        {
            ch = read_char(); 
            switch (ch)
            {
            case 'a':
                ss << '\a';
                break;
            case 'b':
                ss << '\b';
                break;
            case 'f':
                ss << '\f';
                break;
            case 'v':
                ss << '\v';
                break;
            case 'n':
                ss << '\n';
                break;
            case 'r':
                ss << '\r';
                break;
            case 't':
                ss << '\t';
                break;
            case '\\':
                ss << '\\';
                break;
            case '"':
                ss << '"';
                break;
            case 'x':
                {
                    int hex_value = read_hex_escape_sequence();
                    if (hex_value < 0)
                    {
                        // error is logged.
                        return nullptr;
                    }

                    ss << static_cast<char>(hex_value);
                } break;
            default:
                _message_callback(message_utility::unknown_escape_sequence(
                    current_source(),
                    ch));
                return nullptr;
            }
        }
        else
        {
            ss << static_cast<char>(ch);
        }

        ch = _inner.peek();
    }

    if (ch == '"')
    {
        read_char(); // consume the closing quote
    }
    else
    {
        _message_callback(message_utility::unterminated_string_literal(
            current_source()));
        return nullptr;
    }

    std::string str_value = ss.str();
    source_reference source = source_reference(
        start_source.path(),
        start_source.line(),
        start_source.column(),
        _line,
        _column);
    return std::make_shared<string_literal_token>(source, str_value);
}

std::shared_ptr<token> token_reader::read_comment(const source_reference& start_source)
{
    std::ostringstream ss;

    // 1st slash is already read and the 2nd char to make a comment is already determined.
    int ch = _inner.peek();
    if (ch == '/')
    {
        ch = read_char(); // consume the second '/'
        while (ch > 0 && ch != '\n')
        {
            ss << static_cast<char>(ch);
            ch = read_char();
        }

        std::string comment_text = ss.str();
        source_reference source = source_reference(
            start_source.path(),
            start_source.line(),
            start_source.column(),
            _line,
            _column);
        return std::make_shared<comment_token>(source, comment_text);
    }
    else
    {
        read_char(); // consume the '*'
        std::ostringstream ss;
        ch = read_char();
        while (true)
        {
            if (ch == EOF)
            {
                _message_callback(message(
                    current_source(),
                    message_id("OD", 1),
                    severity::SEVERITY_ERROR,
                    "Unterminated block comment."));
                break;
            }
            else if (ch == '*')
            {
                int next_ch = _inner.peek();
                if (next_ch == '/')
                {
                    read_char(); // consume the '/'
                    break;
                }
                else
                {
                    ss << static_cast<char>(ch);
                    ch = read_char();
                }
            }
            else
            {
                ss << static_cast<char>(ch);
                ch = read_char();
            }
        }

        std::string comment_text = ss.str();
        source_reference source = source_reference(
            start_source.path(),
            start_source.line(),
            start_source.column(),
            _line,
            _column);
        return std::make_shared<comment_token>(source, comment_text);
    }
}

int token_reader::read_hex_escape_sequence()
{
    int value = 0;
    int ch = peek_hex_digit();
    if (ch < 0)
    {
        _message_callback(
            message_utility::invalid_hex_escape_sequence(
                current_source(),
                static_cast<char>(ch)));
        return -1; // invalid hex digit
    }

    read_char();
    value = ch;
    ch = peek_hex_digit();
    if (ch >= 0)
    {
        read_char();
        value = (value << 4) | ch;
    }

    return value;
}

int token_reader::peek_hex_digit()
{
    int ch = _inner.peek();
    if (ch >= '0' && ch <= '9')
    {
        return ch - '0';
    }
    else if (ch >= 'a' && ch <= 'f')
    {
        return 10 + (ch - 'a');
    }
    else if (ch >= 'A' && ch <= 'F')
    {
        return 10 + (ch - 'A');
    }
    else
    {
        return -1; // not a hex digit
    }
}

void token_reader::skip_whitespace()
{
    int ch = _inner.peek();
    while (is_whitespace(ch))
    {
        read_char();
        ch = _inner.peek();
    }
}

int token_reader::read_char()
{
    int ch = _inner.get();
    if (ch == '\n')
    {
        _line++;
        _column = 1;
    }
    else
    {
        _column++;
    }

    return ch;
}

