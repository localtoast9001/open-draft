/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 * Licensed under the MIT license. See LICENSE file in the project root for full license information.
 * @file asserts.cpp
 * @brief Contains the implementation of the assert functions.
 */
#include <testfx.hpp>

namespace testfx
{
    void assert_equal(
        const char* expected,
        const char* actual,
        const std::source_location& location)
    {
        if (std::string(expected) != std::string(actual))
        {
            std::ostringstream oss;
            oss << "Assertion failed: expected [" << expected << "], got [" << actual << "]";
            throw assert_exception(oss.str(), location);
        }
    }
}