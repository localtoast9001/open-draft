/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 * Licensed under the MIT license. See LICENSE file in the project root for full license information.
 * @file token.cpp
 * @brief Defines the token class and related functions.
 */
#include <token.hpp>

namespace opendraft::lang
{
    token::token(const source_reference& source)
        : _source(source)
    {
    }
}