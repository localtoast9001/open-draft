/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 * Licensed under the MIT license. See LICENSE file in the project root for full license information.
 * @file assert_exception.cpp
 * @brief Contains the implementation of the assert_exception class.
 */
#include <testfx.hpp>

namespace testfx
{
    assert_exception::assert_exception(
        const std::string& message,
        const std::source_location& location)
        : _message(message), _location(location)
    {
    }
}