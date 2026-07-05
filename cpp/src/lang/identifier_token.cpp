/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 * Licensed under the MIT license. See LICENSE file in the project root for full license information.
 * @file identifier_token.cpp
 * @brief Defines the identifier_token class and related functions.
 */
#include <token.hpp>

namespace opendraft::lang
{
    identifier_token::identifier_token(const source_reference& source, const std::string& name)
        : token(source), _name(name)
    {
    }

    token::token_type identifier_token::type() const
    {
        return token_type::IDENTIFIER;
    }

    std::string identifier_token::to_string() const
    {
        return _name;
    }
}