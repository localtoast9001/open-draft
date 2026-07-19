/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 * Licensed under the MIT license. See LICENSE file in the project root for full license information.
 * @file message_utility.hpp
 * @brief Declares the message_utility class and related functions.
 */

#pragma once
#ifndef __MESSAGE_UTILITY_HPP__
#define __MESSAGE_UTILITY_HPP__

#include <message.hpp>
#include <token.hpp>
#include <memory>

namespace opendraft::lang
{
    /**
     * @brief A utility class for defining and producing messages.
     */
    class message_utility
    {
    public:
        //
        // Lexer message ids.
        //

        static const message_id UNTERMINATED_STRING_LITERAL_ID;
        static const message_id UNRECOGNIZED_CHARACTER_ID;
        static const message_id UNTERMINATED_MULTI_LINE_COMMENT_ID;
        static const message_id UNKNOWN_ESCAPE_SEQUENCE_ID;
        static const message_id INVALID_HEX_ESCAPE_SEQUENCE_ID;
        static const message_id EXPECTED_DECIMAL_EXPONENT_ID;
        static const message_id INVALID_UNIT_SPECIFIER_ID;
        static const message_id INVALID_NUMBER_AFTER_RADIX_ID;

        //
        // Parser message ids.
        //
        static const message_id UNEXPECTED_END_OF_FILE_ID;
        static const message_id KEYWORD_EXPECTED_ID;
        static const message_id SYMBOL_EXPECTED_ID;
        static const message_id IDENTIFIER_EXPECTED_ID;
        static const message_id STRING_LITERAL_EXPECTED_ID;
        static const message_id NUMERIC_LITERAL_EXPECTED_ID;
        static const message_id INTEGER_LITERAL_EXPECTED_ID;
        static const message_id VARIABLE_NAME_EXPECTED_AFTER_TYPE_REFERENCE_ID;
        static const message_id UNEXPECTED_TOKEN_ID;

        //
        // Helper routines for producing messages.
        //

        //
        // Lexer messages.
        //

        static message unterminated_string_literal(const source_reference& source);
        static message unrecognized_character(const source_reference& source, char ch);
        static message unterminated_multi_line_comment(const source_reference& source);
        static message unknown_escape_sequence(const source_reference& source, char ch);
        static message invalid_hex_escape_sequence(const source_reference& source, char ch);
        static message expected_decimal_exponent(const source_reference& source);
        static message invalid_unit_specifier(const source_reference& source, const std::string_view& unit);
        static message invalid_number_after_radix(const source_reference& source);

        //
        // Parser messages.
        //
        static message unexpected_end_of_file(const source_reference& source);
        static message keyword_expected(
            const std::shared_ptr<token>& token, 
            const source_reference& file_source,
            keyword keyword);
        static message symbol_expected(
            const std::shared_ptr<token>& token,
            const source_reference& file_source,
            symbol symbol);
        static message identifier_expected(
            const std::shared_ptr<token>& token,
            const source_reference& file_source);
        static message string_literal_expected(
            const std::shared_ptr<token>& token,
            const source_reference& file_source);
        static message numeric_literal_expected(
            const std::shared_ptr<token>& token,
            const source_reference& file_source);
        static message integer_literal_expected(
            const std::shared_ptr<token>& token,
            const source_reference& file_source);
        static message variable_name_expected_after_type_reference(
            const std::shared_ptr<token>& token,
            const source_reference& file_source);
        static message unexpected_token(
            const std::shared_ptr<token>& token,
            const source_reference& file_source);
    private:
        message_utility() = delete;
        ~message_utility() = delete;
    };
}

#endif /* __MESSAGE_UTILITY_HPP__ */