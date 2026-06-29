/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 * Licensed under the MIT license. See LICENSE file in the project root for full license information.
 * @file test_result.cpp
 * @brief Contains the definitions for the test_result class.
 */
#include <testfx.hpp>

namespace testfx
{
    test_result::test_result()
        : _passed(false), _message(), _duration()
    {
    }

    void test_result::pass(const std::chrono::duration<double>& duration)
    {
        _passed = true;
        _duration = duration;
    }

    void test_result::fail(const std::string& message, const std::chrono::duration<double>& duration)
    {
        _passed = false;
        _message = message;
        _duration = duration;
    }
}