/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 * Licensed under the MIT license. See LICENSE file in the project root for full license information.
 * @file keyword.cpp
 * @brief Defines the keyword enum and related functions.
 */
#include <keyword.hpp>

namespace opendraft::lang
{
    const char* keyword_to_string_map[] = 
    {
        "<undefined>",
        "if",
        "interface",
        "else",
        "for",
        "return",
        "break",
        "continue",
        "function",
        "template",
        "class",
        "true",
        "false",
        "null"
    };

    const char* to_string(keyword value)
    {
        if (static_cast<int>(value) < 0 || static_cast<int>(value) >= sizeof(keyword_to_string_map) / sizeof(keyword_to_string_map[0]))
        {
            return keyword_to_string_map[0];
        }

        return keyword_to_string_map[static_cast<int>(value)];
    }

    /**
     * @brief Converts a string to a keyword enum value.
     * @param str The string to convert.
     * @return The corresponding keyword enum value. If the string does not match any keyword, returns KEYWORD_UNDEFINED.
     */
    keyword keyword_from_string(const std::string_view& str)
    {
        for (int i = 1; i < sizeof(keyword_to_string_map) / sizeof(keyword_to_string_map[0]); ++i)
        {
            if (str == keyword_to_string_map[i])
            {
                return static_cast<keyword>(i);
            }
        }

        return keyword::KEYWORD_UNDEFINED;
    }


    std::ostream& operator<<(std::ostream& os, keyword value)
    {
        os << to_string(value);
        return os;
    }
}