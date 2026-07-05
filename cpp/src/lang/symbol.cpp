/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 * Licensed under the MIT license. See LICENSE file in the project root for full license information.
 * @file symbol.cpp
 * @brief Defines the symbol enum and related functions.
 */

#include <symbol.hpp>

namespace opendraft::lang
{
    const char* symbol_to_string_map[] = 
    {
        "<undefined>",
        "~",
        "%",
        "&",
        "&&",
        "*",
        "(",
        ")",
        "-",
        "+",
        "=",
        "==",
        "!=",
        "[",
        "]",
        "{",
        "}",
        "/",
        "|",
        "||",
        ":",
        ";",
        ",",
        "<",
        "<=",
        ">",
        ">=",
        "<<",
        ">>",
        "?",
        "??",
        ".",
        "..",
        "!",
    };

    const char* to_string(symbol value)
    {
        if (static_cast<int>(value) < 0 || static_cast<int>(value) >= sizeof(symbol_to_string_map) / sizeof(symbol_to_string_map[0]))
        {
            return symbol_to_string_map[0];
        }

        return symbol_to_string_map[static_cast<int>(value)];
    }

    std::ostream& operator<<(std::ostream& os, symbol value)
    {
        os << to_string(value);
        return os;
    }
}