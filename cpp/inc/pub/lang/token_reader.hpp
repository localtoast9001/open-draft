/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 * Licensed under the MIT license. See LICENSE file in the project root for full license information.
 * @file token_reader.hpp
 * @brief Declares the token_reader class.
 */
#pragma once

#ifndef __OPENDRAFT_LANG_TOKEN_READER_HPP__
#define __OPENDRAFT_LANG_TOKEN_READER_HPP__

#include "token.hpp"
#include "source_reference.hpp"
#include "message.hpp"
#include <memory>
#include <istream>
#include <functional>

namespace opendraft::lang
{
    /**
     * @brief Represents a token reader that reads tokens from an input stream.
     * @remarks This is the lexer for the OpenDraft language. It reads tokens from an input stream and produces a stream of tokens that can be consumed by a parser. The token_reader is responsible for handling whitespace, comments, and other non-token elements in the input stream.
     */
    class token_reader
    {
    public:
        token_reader(
            std::istream& inner,
            const source_reference& start_source,
            std::function<void(const message&)> message_callback);
        virtual ~token_reader() = default;

        /**
         * @brief Peeks at the next token in the stream without consuming it.
         * @return A shared pointer to the next token in the stream.
         */
        std::shared_ptr<token> peek();

        /**
         * @brief Reads the next token from the stream and consumes it.
         * @return A shared pointer to the next token in the stream.
         */
        std::shared_ptr<token> read();

        inline source_reference current_source() const
        {
            return source_reference(
                _start_source.path(),
                _line,
                _column);
        }

    private:
        std::istream& _inner;
        source_reference _start_source;
        int _line;
        int _column;
        std::shared_ptr<token> _peeked_token;
        std::function<void(const message&)> _message_callback;

        static bool is_whitespace(int ch);
        static bool is_identifier_start(int ch);
        static bool is_digit(int ch);

        std::shared_ptr<token> inner_read();
        std::shared_ptr<token> read_keyword_or_identifier();
        std::shared_ptr<token> read_comment(const source_reference& start_source);
        std::shared_ptr<token> read_string_literal();
        std::shared_ptr<token> read_numeric_literal();
        std::shared_ptr<token> read_decimal_literal(const source_reference& start_source, long int_part);
        std::shared_ptr<token> read_symbol();
        int read_hex_escape_sequence();
        int peek_hex_digit();

        void skip_whitespace();

        int read_char();

        // disable copy semantics for token_reader.
        token_reader(const token_reader&) = delete;
        token_reader& operator=(const token_reader&) = delete;
    };
}
#endif /* __OPENDRAFT_LANG_TOKEN_READER_HPP__ */