/**
 * Copyright (C) Jon Rowlett. All rights reserved.
 * Licensed under the MIT license. See LICENSE file in the project root for full license information.
 * @file float_utility_test.cpp
 * @brief Contains the unit tests for the float_utility class.
 */
#include <testfx.hpp>
#include <float_utility.hpp>
#include <tuple>

using namespace std;
using namespace opendraft::lang;
using namespace testfx;

class float_utility_test : public test_class
{
public:
    static float_utility_test instance;

    float_utility_test();

    void mul_pow10_test_compiler_constants();
    void compose_test_strtod();
};

float_utility_test float_utility_test::instance;

float_utility_test::float_utility_test()
: test_class("float_utility_test")
{
    add("mul_pow10_test_compiler_constants", (test_method)&float_utility_test::mul_pow10_test_compiler_constants);
    add("compose_test_strtod", (test_method)&float_utility_test::compose_test_strtod);
}

void float_utility_test::mul_pow10_test_compiler_constants()
{
    tuple<double, int, double> test_cases[] = {
        { 1.0, 0, 1.0 },
        { 1.0, 1, 10.0 },
        { 1.0, -1, 0.1 },
        { 2.5, 2, 250.0 },
        { 2.5, -2, 0.025 },
        { -3.14, 3, -3140.0 },
        { -3.14, -3, -0.00314 },
        { 123.456, -3, 123.456e-3 },
    };

    for (const auto& [base, exponent, expected] : test_cases)
    {
        double result = float_utility::mul_pow10(base, exponent);
        assert_equal(expected, result);
    }
}

void float_utility_test::compose_test_strtod()
{
    tuple<string, long, long, long, int> test_cases[] = {
        { "1.0", 1, 0, -1, 0 },
        { "1.0e1", 1, 0, -1, 1 },
        { "1.0e-1", 1, 0, -1, -1 },
        { "2.5e2", 2, 5, -1, 2 },
        { "2.5e-2", 2, 5, -1, -2 },
        { "-3.14e3", -3, -14, -2, 3 },
        { "-3.14e-3", -3, -14, -2, -3 },
        { "123.456e-3", 123, 456, -3, -3 },
    };

    for (const auto& [input, int_part, frac_part, divisor, exponent] : test_cases)
    {
        double result = float_utility::compose(int_part, frac_part, divisor, exponent);
        char* endptr = nullptr;
        double expected = std::strtod(input.c_str(), &endptr);
        assert_equal(expected, result);
    }
}