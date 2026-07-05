/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 * Licensed under the MIT license. See LICENSE file in the project root for full license information.
 * @file severity.cpp
 * @brief Defines the severity enum and related functions.
 */
#include <message.hpp>

namespace opendraft::lang
{
    const char* severity_to_string_map[] = 
    {
        "error",
        "warning",
        "info"
    };

    const char* to_string(severity value)
    {
        if (static_cast<int>(value) < 0 || static_cast<int>(value) >= sizeof(severity_to_string_map) / sizeof(severity_to_string_map[0]))
        {
            return "unknown";
        }

        return severity_to_string_map[static_cast<int>(value)];
    }
}
