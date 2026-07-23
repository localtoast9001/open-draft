/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 * Licensed under the MIT license. See LICENSE file in the project root for full license information.
 * @file token.hpp
 * @brief Defines the token class.
 */
#pragma once

#ifndef __OPENDRAFT_LANG_TOKEN_HPP__
#define __OPENDRAFT_LANG_TOKEN_HPP__

#include "source_reference.hpp"
#include "keyword.hpp"
#include "symbol.hpp"

namespace opendraft::lang
{
    /**
     * @brief Represents a token in the source code.
     * @remarks This is the base class for all tokens produced by the token_reader lexer.
     * Tokens are meant to be immutable and passed around by reference using std::shared_ptr. The type of the token can be determined using the type() method, which returns an enum value representing the token's type.
     */
    class token
    {
    public:
        /**
         * @brief Represents the type of the token.
         * @remarks This is used instead of RTTI to avoid the overhead of dynamic_cast and typeid.
         */
        enum token_type
        {
            UNDEFINED = 0,
            IDENTIFIER,
            KEYWORD,
            SYMBOL,
            STRING_LITERAL,
            NUMERIC_LITERAL,
            COMMENT,
        };

        virtual ~token() = default;

        /**
         * @brief Gets the source reference associated with the token.
         * @return The source reference associated with the token.
         */
        constexpr const source_reference& source() const { return _source; }

        /**
         * @brief Gets the type of the token.
         * @return The type of the token.
         */
        virtual token_type type() const = 0;

        /**
         * @brief Converts the token to a string representation.
         * @return A string representation of the token.
         */
        virtual std::string to_string() const = 0;

    protected:
        /**
         * @brief Constructs a new token object.
         */
        token(const source_reference& source);
    private:
        source_reference _source;

        token(const token&) = delete;
        token& operator=(const token&) = delete;
    };

    /**
     * @brief Represents an identifier token in the source code.
     */
    class identifier_token : public token
    {
    public:
        identifier_token(const source_reference& source, const std::string& name);
        virtual token_type type() const override;
        const std::string& name() const { return _name; }

        virtual std::string to_string() const override;
    private:
        std::string _name;
    };

    /**
     * @brief Represents a keyword token in the source code.
     */
    class keyword_token : public token
    {
    public:
        keyword_token(const source_reference& source, keyword value);
        virtual token_type type() const override;
        keyword value() const { return _value; }

        virtual std::string to_string() const override;

    private:
        keyword _value;
    };

    /**
     * @brief Represents a symbol token in the source code.
     */
    class symbol_token : public token
    {
    public:
        symbol_token(const source_reference& source, symbol value);
        virtual token_type type() const override;
        constexpr symbol value() const { return _value; }
        virtual std::string to_string() const override;

    private:
        symbol _value;
    };

    class string_literal_token : public token
    {
    public:
        string_literal_token(const source_reference& source, const std::string& value);
        virtual token_type type() const override;
        const std::string& value() const { return _value; }
        virtual std::string to_string() const override;

    private:    
        std::string _value;
    };

    /**
     * @brief Represents a numeric literal token in the source code.
     */
    class numeric_literal_token : public token
    {
    public:
        numeric_literal_token(
            const source_reference& source,
            long value,
            const std::string& unit = std::string());
        numeric_literal_token(
            const source_reference& source,
            double value,
            const std::string& unit = std::string());
        virtual token_type type() const override;

        constexpr bool is_integer() const { return _is_integer; }
        constexpr long integer_value() const { return _integer_value; }
        constexpr double double_value() const { return _double_value; }
        constexpr const std::string& unit() const { return _unit; }

        virtual std::string to_string() const override;

    private:
        bool _is_integer;
        long _integer_value;
        double _double_value;
        std::string _unit;
    };

    /**
     * @brief Represents a comment token in the source code.
     */
    class comment_token : public token
    {
    public:
        comment_token(const source_reference& source, const std::string& text);
        virtual token_type type() const override;
        const std::string& text() const { return _text; }

        virtual std::string to_string() const override;

    private:
        std::string _text;
    };
}

#endif /* __OPENDRAFT_LANG_TOKEN_HPP__ */