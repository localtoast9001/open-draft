/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 * Licensed under the MIT license. See LICENSE file in the project root for full license information.
 * @file symbol_token.cpp
 * @brief Defines the symbol_token class and related functions.
 */
#include <token.hpp>

namespace opendraft::lang
{
    symbol_token::symbol_token(const source_reference& source, symbol value)
        : token(source), _value(value)
    {
    }

    token::token_type symbol_token::type() const
    {
        return token_type::SYMBOL;
    }

    std::string symbol_token::to_string() const
    {
        return std::string(opendraft::lang::to_string(_value));
    }
}