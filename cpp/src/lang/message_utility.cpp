/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 * Licensed under the MIT license. See LICENSE file in the project root for full license information.
 * @file message_utility.cpp
 * @brief Implements the message_utility class and related functions.
 */

#include "message_utility.hpp"

namespace opendraft::lang
{
    constexpr char DEFAULT_CATEGORY[] = "ODL";
    const message_id message_utility::UNTERMINATED_STRING_LITERAL_ID(DEFAULT_CATEGORY, 1000);
    const message_id message_utility::UNRECOGNIZED_CHARACTER_ID(DEFAULT_CATEGORY, 1001);
    const message_id message_utility::UNTERMINATED_MULTI_LINE_COMMENT_ID(DEFAULT_CATEGORY, 1002);
    const message_id message_utility::UNKNOWN_ESCAPE_SEQUENCE_ID(DEFAULT_CATEGORY, 1003);
    const message_id message_utility::INVALID_HEX_ESCAPE_SEQUENCE_ID(DEFAULT_CATEGORY, 1004);
    const message_id message_utility::EXPECTED_DECIMAL_EXPONENT_ID(DEFAULT_CATEGORY, 1005);
    const message_id message_utility::INVALID_UNIT_SPECIFIER_ID(DEFAULT_CATEGORY, 1006);
    const message_id message_utility::INVALID_NUMBER_AFTER_RADIX_ID(DEFAULT_CATEGORY, 1007);

    const message_id message_utility::UNEXPECTED_END_OF_FILE_ID(DEFAULT_CATEGORY, 2000);
    const message_id message_utility::KEYWORD_EXPECTED_ID(DEFAULT_CATEGORY, 2001);
    const message_id message_utility::SYMBOL_EXPECTED_ID(DEFAULT_CATEGORY, 2002);
    const message_id message_utility::IDENTIFIER_EXPECTED_ID(DEFAULT_CATEGORY, 2003);
    const message_id message_utility::STRING_LITERAL_EXPECTED_ID(DEFAULT_CATEGORY, 2004);
    const message_id message_utility::NUMERIC_LITERAL_EXPECTED_ID(DEFAULT_CATEGORY, 2005);
    const message_id message_utility::INTEGER_LITERAL_EXPECTED_ID(DEFAULT_CATEGORY, 2006);
    const message_id message_utility::VARIABLE_NAME_EXPECTED_AFTER_TYPE_REFERENCE_ID(DEFAULT_CATEGORY, 2007);
    const message_id message_utility::UNEXPECTED_TOKEN_ID(DEFAULT_CATEGORY, 2100);

    message message_utility::unterminated_string_literal(const source_reference& source)
    {
        return message(
            source,
            UNTERMINATED_STRING_LITERAL_ID,
            severity::SEVERITY_ERROR,
            "unterminated string literal");
    }

    message message_utility::unrecognized_character(const source_reference& source, char ch)
    {
        return message(
            source,
            UNRECOGNIZED_CHARACTER_ID,
            severity::SEVERITY_ERROR,
            "unrecognized character");
    }

    message message_utility::unterminated_multi_line_comment(const source_reference& source)
    {
        return message(
            source,
            UNTERMINATED_MULTI_LINE_COMMENT_ID,
            severity::SEVERITY_ERROR,
            "unterminated multi-line comment");
    }

    message message_utility::unknown_escape_sequence(const source_reference& source, char ch)
    {
        return message(
            source,
            UNKNOWN_ESCAPE_SEQUENCE_ID,
            severity::SEVERITY_ERROR,
            "unknown escape sequence");
    }

    message message_utility::invalid_hex_escape_sequence(const source_reference& source, char ch)
    {
        return message(
            source,
            INVALID_HEX_ESCAPE_SEQUENCE_ID,
            severity::SEVERITY_ERROR,
            "invalid hex escape sequence");
    }

    message message_utility::expected_decimal_exponent(const source_reference& source)
    {
        return message(
            source,
            EXPECTED_DECIMAL_EXPONENT_ID,
            severity::SEVERITY_ERROR,
            "expected decimal exponent");
    }

    message message_utility::invalid_unit_specifier(const source_reference& source, const std::string_view& unit)
    {
        return message(
            source,
            INVALID_UNIT_SPECIFIER_ID,
            severity::SEVERITY_ERROR,
            "invalid unit specifier");
    }

    message message_utility::invalid_number_after_radix(const source_reference& source)
    {
        return message(
            source,
            INVALID_NUMBER_AFTER_RADIX_ID,
            severity::SEVERITY_ERROR,
            "invalid number after radix");
    }

    message message_utility::unexpected_end_of_file(const source_reference& source)
    {
        return message(
            source,
            UNEXPECTED_END_OF_FILE_ID,
            severity::SEVERITY_ERROR,
            "unexpected end of file");
    }

    message message_utility::keyword_expected(
        const std::shared_ptr<token>& token, 
        const source_reference& file_source,
        keyword keyword)
    {
        return message(
            token->source(),
            KEYWORD_EXPECTED_ID,
            severity::SEVERITY_ERROR,
            "keyword expected");
    }

    message message_utility::symbol_expected(
        const std::shared_ptr<token>& token,
        const source_reference& file_source,
        symbol symbol)
    {
        return message(
            token->source(),
            SYMBOL_EXPECTED_ID,
            severity::SEVERITY_ERROR,
            "symbol expected");
    }

    message message_utility::identifier_expected(
        const std::shared_ptr<token>& token,
        const source_reference& file_source)
    {
        return message(
            token->source(),
            IDENTIFIER_EXPECTED_ID,
            severity::SEVERITY_ERROR,
            "identifier expected");
    }

    message message_utility::string_literal_expected(
        const std::shared_ptr<token>& token,
        const source_reference& file_source)
    {
        return message(
            token->source(),
            STRING_LITERAL_EXPECTED_ID,
            severity::SEVERITY_ERROR,
            "string literal expected");
    }

    message message_utility::numeric_literal_expected(
        const std::shared_ptr<token>& token,
        const source_reference& file_source)
    {
        return message(
            token->source(),
            NUMERIC_LITERAL_EXPECTED_ID,
            severity::SEVERITY_ERROR,
            "numeric literal expected");
    }

    message message_utility::integer_literal_expected(
        const std::shared_ptr<token>& token,
        const source_reference& file_source)
    {
        return message(
            token->source(),
            INTEGER_LITERAL_EXPECTED_ID,
            severity::SEVERITY_ERROR,
            "integer literal expected");
    }

    message message_utility::variable_name_expected_after_type_reference(
        const std::shared_ptr<token>& token,
        const source_reference& file_source)
    {
        return message(
            token->source(),
            VARIABLE_NAME_EXPECTED_AFTER_TYPE_REFERENCE_ID,
            severity::SEVERITY_ERROR,
            "variable name expected after type reference");
    }

    message message_utility::unexpected_token(
        const std::shared_ptr<token>& token,
        const source_reference& file_source)
    {
        return message(
            token->source(),
            UNEXPECTED_TOKEN_ID,
            severity::SEVERITY_ERROR,
            "unexpected token");
    }
}
