/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 * Licensed under the MIT license. See LICENSE file in the project root for full license information.
 * @file token_reader.cpp
 * @brief Defines the token_reader class and related functions.
 */
#include <token_reader.hpp>
#include <sstream>
#include <cmath>

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

bool token_reader::is_digit(int ch)
{
    return ch >= '0' && ch <= '9';
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
    while (is_identifier_start(ch) || is_digit(ch))
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
    while (is_digit(ch))
    {
        read_char();
        int_part = int_part * 10 + (ch - '0');
        ch = _inner.peek();
    }

    if (ch == '.')
    {
        read_char();
        return read_decimal_literal(start_source, int_part);
    }
    else
    {
        source_reference source = source_reference(
            start_source.path(),
            start_source.line(),
            start_source.column(),
            _line,
            _column);
        return std::make_shared<numeric_literal_token>(source, int_part);
    }
}

std::shared_ptr<token> token_reader::read_decimal_literal(
    const source_reference& start_source,
    long int_part)
{
    // the decimal point has already been read.
    double frac_part = 0.0;
    double multiplier = 0.1;
    int ch = _inner.peek();
    while (is_digit(ch))
    {
        read_char();
        frac_part += (ch - '0') * multiplier;
        multiplier *= 0.1;
        ch = _inner.peek();
    }

    int exponent = 0;
    bool exponent_negative = false;
    if (ch == 'e' || ch == 'E')
    {
        read_char();
        ch = _inner.peek();
        if (ch == '+' || ch == '-')
        {
            exponent_negative = (ch == '-');
            read_char();
            ch = _inner.peek();
        }
        while (is_digit(ch))
        {
            read_char();
            exponent = exponent * 10 + (ch - '0');
            ch = _inner.peek();
        }
    }

    double value = int_part + frac_part;
    if (exponent != 0)
    {
        if (exponent_negative)
        {
            exponent = -exponent;
        }

        value *= std::pow(10.0, exponent);
    }

    source_reference source = source_reference(
        start_source.path(),
        start_source.line(),
        start_source.column(),
        _line,
        _column);
    return std::make_shared<numeric_literal_token>(source, value);
}

std::shared_ptr<token> token_reader::read_string_literal()
{
    source_reference start_source = current_source();
    std::ostringstream ss;
    int ch = read_char(); // consume the opening quote
    ch = _inner.peek();
    while (ch != '"')
    {
        if (ch == EOF)
        {
            _message_callback(message(
                current_source(),
                message_id("OD", 2),
                severity::SEVERITY_ERROR,
                "Unterminated string literal."));
            break;
        }
        else if (ch == '\\')
        {
            read_char(); // consume the backslash
            ch = _inner.peek();
            switch (ch)
            {
            case 'n':
                ss << '\n';
                break;
            case 't':
                ss << '\t';
                break;
            case 'r':
                ss << '\r';
                break;
            case '\\':
                ss << '\\';
                break;
            case '"':
                ss << '"';
                break;
            default:
                ss << static_cast<char>(ch);
                break;
            }
        }
        else
        {
            read_char(); // consume the character
            ss << static_cast<char>(ch);
        }

        ch = _inner.peek();
    }

    read_char(); // consume the closing quote

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

