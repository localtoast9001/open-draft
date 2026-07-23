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
        const source_reference& source,
        long value,
        const std::string& unit)
        : token(source), _integer_value(value), _is_integer(true), _unit(unit)
    {
    }

    numeric_literal_token::numeric_literal_token(
        const source_reference& source,
        double value,
        const std::string& unit)
        : token(source), _double_value(value), _is_integer(false), _unit(unit)
    {
    }

    token::token_type numeric_literal_token::type() const
    {
        return token_type::NUMERIC_LITERAL;
    }

    std::string numeric_literal_token::to_string() const
    {
        auto str = _is_integer ? 
            std::to_string(_integer_value) : 
            std::format("{:g}", _double_value);
        return str + _unit;
    }
}