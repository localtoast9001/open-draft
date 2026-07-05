/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 * Licensed under the MIT license. See LICENSE file in the project root for full license information.
 * @file keyword.hpp
 * @brief Declares the keyword enum and related functions.
 */
#pragma once

#ifndef __OPENDRAFT_LANG_KEYWORD_HPP__
#define __OPENDRAFT_LANG_KEYWORD_HPP__

#include <ostream>

namespace opendraft::lang
{
    /**
     * @brief Represents the keywords in the OpenDraft language.
     */
    enum class keyword
    {
        KEYWORD_UNDEFINED = 0,
        KEYWORD_IF,
        KEYWORD_INTERFACE,
        KEYWORD_ELSE,
        KEYWORD_FOR,
        KEYWORD_RETURN,
        KEYWORD_BREAK,
        KEYWORD_CONTINUE,
        KEYWORD_FUNCTION,
        KEYWORD_TEMPLATE,
        KEYWORD_CLASS,
        KEYWORD_TRUE,
        KEYWORD_FALSE,
        KEYWORD_NULL,
    };

    /**
     * @brief Converts a keyword enum value to its string representation.
     * @param value The keyword enum value to convert.
     * @return The string representation of the keyword.
     */
    const char* to_string(keyword value);

    /**
     * @brief Converts a string to a keyword enum value.
     * @param str The string to convert.
     * @return The corresponding keyword enum value. If the string does not match any keyword, returns KEYWORD_UNDEFINED.
     */
    keyword keyword_from_string(const std::string_view& str);

    std::ostream& operator<<(std::ostream& os, keyword value);
}
#endif /* __OPENDRAFT_LANG_KEYWORD_HPP__ */