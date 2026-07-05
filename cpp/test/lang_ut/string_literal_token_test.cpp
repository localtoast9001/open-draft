/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 * Licensed under the MIT license. See LICENSE file in the project root for full license information.
 * @file string_literal_token_test.cpp
 * @brief unit tests for the string_literal_token class.
 */
#include <token.hpp>
#include <testfx.hpp>

using namespace testfx;
using namespace opendraft::lang;

class string_literal_token_test : public test_class
{
public:
    static string_literal_token_test instance;

    string_literal_token_test();
    void constructor_test();
    void to_string_test();
};

string_literal_token_test string_literal_token_test::instance;

string_literal_token_test::string_literal_token_test()
: test_class("string_literal_token_test")
{
    add("constructor_test", (test_method)&string_literal_token_test::constructor_test);
    add("to_string_test", (test_method)&string_literal_token_test::to_string_test);
}

void string_literal_token_test::constructor_test()
{
    auto ref = source_reference("test.od", 5);
    auto target = std::make_shared<string_literal_token>(ref, "Hello, World!");
    assert_equal(ref, target->source());
    assert_equal(token::token_type::STRING_LITERAL, target->type());
    assert_equal(std::string("Hello, World!"), target->value());
}

void string_literal_token_test::to_string_test()
{
    auto ref = source_reference("test.od", 5);
    auto target = std::make_shared<string_literal_token>(ref, "Hello, World!");
    assert_equal(std::string("Hello, World!"), target->to_string());
}