/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 * Licensed under the MIT license. See LICENSE file in the project root for full license information.
 * @file keyword_token.cpp
 * @brief Defines the keyword_token class and related functions.
 */
#include <token.hpp>

namespace opendraft::lang
{
    keyword_token::keyword_token(const source_reference& source, keyword value)
        : token(source), _value(value)
    {
    }

    token::token_type keyword_token::type() const
    {
        return token_type::KEYWORD;
    }

    std::string keyword_token::to_string() const
    {
        return std::string(opendraft::lang::to_string(_value));
    }
}