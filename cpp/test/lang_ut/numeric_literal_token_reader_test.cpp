/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 * Licensed under the MIT license. See LICENSE file in the project root for full license information.
 * @file numeric_literal_token_reader_test.cpp
 * @brief Contains the unit tests for the token_reader class for numeric literals.
 */
#include <testfx.hpp>
#include <token_reader.hpp>
#include "token_reader_test_utility.hpp"

using namespace opendraft::lang;
using namespace testfx;
using namespace std;

class numeric_literal_token_reader_test : public test_class
{
public:
    static numeric_literal_token_reader_test instance;

    numeric_literal_token_reader_test();

    void test_integer_zero();
    void test_basic_integer();
    void test_floating_point_zero();
    void test_starting_decimal_point();
    void test_floating_point_no_exponent();
    void test_full_floating_point();
    void test_full_floating_point_with_uppercase_e();
    void test_full_floating_point_with_negative_exponent();
    void test_integer_with_exponent_lowercase_e();
    void test_integer_with_exponent_uppercase_e();
    void test_integer_with_positive_exponent();
    void test_integer_with_units();
    void test_decimal_with_units();
    void test_hex_number();
    void test_hex_number_with_units();
    void test_octal_number();
    void test_binary_number();
    void test_corner_cases();
    void test_empty_exponent_fails_with_error();
    void test_empty_negative_exponent_fails_with_error();
    void test_empty_positive_exponent_fails_with_error();
    void test_invalid_unit();

private:
    void exponent_error_test(
        const std::string& input,
        const std::source_location& location = std::source_location::current());
};

numeric_literal_token_reader_test numeric_literal_token_reader_test::instance;

numeric_literal_token_reader_test::numeric_literal_token_reader_test()
: test_class("numeric_literal_token_reader_test")
{
    add("test_integer_zero", (test_method)&numeric_literal_token_reader_test::test_integer_zero);
    add("test_basic_integer", (test_method)&numeric_literal_token_reader_test::test_basic_integer);
    add("test_floating_point_zero", (test_method)&numeric_literal_token_reader_test::test_floating_point_zero);
    add("test_starting_decimal_point", (test_method)&numeric_literal_token_reader_test::test_starting_decimal_point);
    add("test_floating_point_no_exponent", (test_method)&numeric_literal_token_reader_test::test_floating_point_no_exponent);
    add("test_full_floating_point", (test_method)&numeric_literal_token_reader_test::test_full_floating_point);
    add("test_full_floating_point_with_uppercase_e", (test_method)&numeric_literal_token_reader_test::test_full_floating_point_with_uppercase_e);
    add("test_full_floating_point_with_negative_exponent", (test_method)&numeric_literal_token_reader_test::test_full_floating_point_with_negative_exponent);
    add("test_integer_with_exponent_lowercase_e", (test_method)&numeric_literal_token_reader_test::test_integer_with_exponent_lowercase_e);
    add("test_integer_with_exponent_uppercase_e", (test_method)&numeric_literal_token_reader_test::test_integer_with_exponent_uppercase_e);
    add("test_integer_with_positive_exponent", (test_method)&numeric_literal_token_reader_test::test_integer_with_positive_exponent);
    add("test_integer_with_units", (test_method)&numeric_literal_token_reader_test::test_integer_with_units);
    add("test_decimal_with_units", (test_method)&numeric_literal_token_reader_test::test_decimal_with_units);
    add("test_hex_number", (test_method)&numeric_literal_token_reader_test::test_hex_number);
    add("test_hex_number_with_units", (test_method)&numeric_literal_token_reader_test::test_hex_number_with_units);
    add("test_octal_number", (test_method)&numeric_literal_token_reader_test::test_octal_number);
    add("test_binary_number", (test_method)&numeric_literal_token_reader_test::test_binary_number);
    add("test_corner_cases", (test_method)&numeric_literal_token_reader_test::test_corner_cases);
    add("test_empty_exponent_fails_with_error", (test_method)&numeric_literal_token_reader_test::test_empty_exponent_fails_with_error);
    add("test_empty_negative_exponent_fails_with_error", (test_method)&numeric_literal_token_reader_test::test_empty_negative_exponent_fails_with_error);
    add("test_empty_positive_exponent_fails_with_error", (test_method)&numeric_literal_token_reader_test::test_empty_positive_exponent_fails_with_error);
    add("test_invalid_unit", (test_method)&numeric_literal_token_reader_test::test_invalid_unit);
}

void numeric_literal_token_reader_test::test_integer_zero()
{
    token_reader_test_utility::single_token_clean_test(0L, "0");
}

void numeric_literal_token_reader_test::test_basic_integer()
{
    token_reader_test_utility::single_token_clean_test(123L, "123");
}

void numeric_literal_token_reader_test::test_floating_point_zero()
{
    token_reader_test_utility::single_token_clean_test(0.0, "0.0");
}

void numeric_literal_token_reader_test::test_starting_decimal_point()
{
    token_reader_test_utility::single_token_clean_test(0.123, ".123");
}

void numeric_literal_token_reader_test::test_floating_point_no_exponent()
{
    token_reader_test_utility::single_token_clean_test(123.456, "123.456");
}

void numeric_literal_token_reader_test::test_full_floating_point()
{
    token_reader_test_utility::single_token_clean_test(123.456e7, "123.456e7");
}

void numeric_literal_token_reader_test::test_full_floating_point_with_uppercase_e()
{
    token_reader_test_utility::single_token_clean_test(123.456E7, "123.456E7");
}

void numeric_literal_token_reader_test::test_full_floating_point_with_negative_exponent()
{
    token_reader_test_utility::single_token_clean_test(123.456e-7, "123.456e-7");
}

void numeric_literal_token_reader_test::test_integer_with_exponent_lowercase_e()
{
    token_reader_test_utility::single_token_clean_test(123e4, "123e4");
}

void numeric_literal_token_reader_test::test_integer_with_exponent_uppercase_e()
{
    token_reader_test_utility::single_token_clean_test(123E4, "123E4");
}

void numeric_literal_token_reader_test::test_integer_with_positive_exponent()
{
    token_reader_test_utility::single_token_clean_test(123e4, "123e+4");
}

void numeric_literal_token_reader_test::test_integer_with_units()
{
    token_reader_test_utility::single_token_clean_test(
        123L,
        "123mm",
        "mm");

    token_reader_test_utility::single_token_clean_test(
        60L,
        "60°",
        "°");
    
    token_reader_test_utility::single_token_clean_test(
        60L,
        "60_ft",
        "ft");
}

void numeric_literal_token_reader_test::test_decimal_with_units()
{
    token_reader_test_utility::single_token_clean_test(
        123.456,
        "123.456\"",
        "\"");

    token_reader_test_utility::single_token_clean_test(
        22.5,
        "22.5°",
        "°");
    
    token_reader_test_utility::single_token_clean_test(
        123.456e-3,
        "123.456e-3_r",
        "r");

    token_reader_test_utility::single_token_clean_test(
        3.14,
        "3.14㎭",
        "㎭");
}

void numeric_literal_token_reader_test::test_hex_number()
{
    token_reader_test_utility::single_token_clean_test((long)0x1a3F, "0x1a3F");
    token_reader_test_utility::single_token_clean_test((long)0x1A3F, "0X1A3F");
}

void numeric_literal_token_reader_test::test_hex_number_with_units()
{
    token_reader_test_utility::single_token_clean_test(
        (long)0x1a3F,
        "0x1a3Fmm",
        "mm");
}

void numeric_literal_token_reader_test::test_octal_number()
{
    token_reader_test_utility::single_token_clean_test(
        (long)0123,
        "0o123");
    token_reader_test_utility::single_token_clean_test(
        (long)0123,
        "0O123");
}

void numeric_literal_token_reader_test::test_binary_number()
{
    token_reader_test_utility::single_token_clean_test(
        (long)0b1010,
        "0b1010");
    token_reader_test_utility::single_token_clean_test(
        (long)0b1010,
        "0B1010");
}

void numeric_literal_token_reader_test::test_corner_cases()
{
    tuple<string, double> test_cases[] = {
        { "0.0", 0 },
        { "0e0", 0 },
        { "0.0e0", 0 },
        { "1e-1", 0.1 },
        { "1e-2", 0.01 },
        { "1e-3", 0.001 },
        { "1e-4", 0.0001 },
        { "1e-5", 0.00001 },
        { "1e-6", 0.000001 },
        { "1e-7", 0.0000001 },
        { "1.e+1", 1e1 },
        { "1.", 1 },
    };

    for (const auto& [input, expected] : test_cases)
    {
        token_reader_test_utility::single_token_clean_test(expected, input);
    }
}

void numeric_literal_token_reader_test::test_empty_exponent_fails_with_error()
{
    exponent_error_test("123e");
}

void numeric_literal_token_reader_test::test_empty_negative_exponent_fails_with_error()
{
    exponent_error_test("123e-");
}

void numeric_literal_token_reader_test::test_empty_positive_exponent_fails_with_error()
{
    exponent_error_test("123e+");
}

void numeric_literal_token_reader_test::test_invalid_unit()
{
    test_message_log log;
    std::istringstream ss("123_");
    auto reader = token_reader_test_utility::create_token_reader(ss, log);
    auto token = reader->read();
    assert_equal(false, (bool)token);
    assert_equal((size_t)1, log.messages().size());
    auto msg = log.messages()[0];
    assert_equal(string("ODL1006"), msg.id().to_string());
}

void numeric_literal_token_reader_test::exponent_error_test(
    const std::string& input,
    const std::source_location& location)
{
    test_message_log log;
    std::istringstream ss(input);
    auto reader = token_reader_test_utility::create_token_reader(ss, log, location);
    auto token = reader->read();
    assert_equal(false, (bool)token);
    assert_equal((size_t)1, log.messages().size());
    auto msg = log.messages()[0];
    assert_equal(string("ODL1005"), msg.id().to_string());
}