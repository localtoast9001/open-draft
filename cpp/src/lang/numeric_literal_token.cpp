/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 * Licensed under the MIT license. See LICENSE file in the project root for full license information.
 * @file numeric_literal_token.cpp
 * @brief Defines the numeric_literal_token class and related functions.
 */
#include <token.hpp>
#include <format>

namespace opendraft::lang
{
    numeric_literal_token::numeric_literal_token(
        const source_reference& source, long value)
        : token(source), _integer_value(value), _is_integer(true)
    {
    }

    numeric_literal_token::numeric_literal_token(
        const source_reference& source, double value)
        : token(source), _double_value(value), _is_integer(false)
    {
    }

    token::token_type numeric_literal_token::type() const
    {
        return token_type::NUMERIC_LITERAL;
    }

    std::string numeric_literal_token::to_string() const
    {
        if (_is_integer)
        {
            return std::to_string(_integer_value);
        }
        else
        {
            return std::format("{:g}", _double_value);
        }
    }
}