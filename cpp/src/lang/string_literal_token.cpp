/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 * Licensed under the MIT license. See LICENSE file in the project root for full license information.
 * @file string_literal_token.cpp
 * @brief Defines the string_literal_token class and related functions.
 */
#include <token.hpp>

namespace opendraft::lang
{
    string_literal_token::string_literal_token(const source_reference& source, const std::string& value)
        : token(source), _value(value)
    {
    }

    token::token_type string_literal_token::type() const
    {
        return token_type::STRING_LITERAL;
    }

    std::string string_literal_token::to_string() const
    {
        return _value;
    }
}