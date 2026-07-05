/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 * Licensed under the MIT license. See LICENSE file in the project root for full license information.
 * @file test_summary.cpp
 * @brief Contains the definitions for the test_summary class.
 */

#include <testfx.hpp>

namespace testfx
{
    test_summary::test_summary()
        : _passed_tests(0), _failed_tests(0), _total_duration(0)
    {
    }

    void test_summary::add_result(const test_result& result)
    {
        _total_duration += result.duration();
        if (result.passed())
        {
            ++_passed_tests;
        }
        else
        {
            ++_failed_tests;
        }
    }
}