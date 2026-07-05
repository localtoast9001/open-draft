/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 * Licensed under the MIT license. See LICENSE file in the project root for full license information.
 * @file comment_token.cpp
 * @brief Defines the comment_token class and related functions.
 */
#include <token.hpp>

namespace opendraft::lang
{
    comment_token::comment_token(const source_reference& source, const std::string& text)
        : token(source), _text(text)
    {
    }

    token::token_type comment_token::type() const
    {
        return token_type::COMMENT;
    }

    std::string comment_token::to_string() const
    {
        return "/* " + _text + " */";
    }
}