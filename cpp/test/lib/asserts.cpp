/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 * Licensed under the MIT license. See LICENSE file in the project root for full license information.
 * @file asserts.cpp
 * @brief Contains the implementation of the assert functions.
 */
#include <testfx.hpp>

namespace testfx
{
    template<>
        void assert_equal<double>(
            const double& expected,
            const double& actual,
            const std::source_location& location)
    {
        if (expected != actual)
        {
            long* expected_bits = (long*)&expected;
            long* actual_bits = (long*)&actual;

            std::ostringstream oss;
            oss 
                << "Assertion failed: expected ["
                << expected
                << "] (0x"
                << std::hex
                << *expected_bits
                << "), got [" 
                << actual
                << "] (0x"
                << std::hex
                << *actual_bits
                << ")";
            throw assert_exception(oss.str(), location);
        }
    }

    template<>
    void assert_equal<std::string>(
        const std::string& expected,
        const std::string& actual,
        const std::source_location& location)
    {
        if (expected != actual)
        {
            int index = 0;
            while (index < expected.size() && index < actual.size())
            {
                if (expected[index] != actual[index])
                {
                    break;
                }

                ++index;
            }

            std::ostringstream oss;
            oss << 
                "Assertion failed: expected " << expected.length() << " chars [" << expected <<
                "], got " << actual.length() << " chars [..." << actual.substr(index) << "] (first difference at index " << index << ")";
            throw assert_exception(oss.str(), location);
        }        
    }

    void assert_equal(
        const char* expected,
        const char* actual,
        const std::source_location& location)
    {
        std::string expected_str(expected ? expected : "");
        std::string actual_str(actual ? actual : "");
        assert_equal<std::string>(expected_str, actual_str, location);
    }
}