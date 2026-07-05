/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 * Licensed under the MIT license. See LICENSE file in the project root for full license information.
 * @file numeric_literal_token_test.cpp
 * @brief unit tests for the numeric_literal_token class.
 */
#include <token.hpp>
#include <testfx.hpp>

using namespace testfx;
using namespace opendraft::lang;

class numeric_literal_token_test : public test_class
{
public:
    static numeric_literal_token_test instance;
    numeric_literal_token_test();
    void constructor_test();
    void to_string_test();
};

numeric_literal_token_test numeric_literal_token_test::instance;

numeric_literal_token_test::numeric_literal_token_test()
: test_class("numeric_literal_token_test")
{
    add("constructor_test", (test_method)&numeric_literal_token_test::constructor_test);
    add("to_string_test", (test_method)&numeric_literal_token_test::to_string_test);
}

void numeric_literal_token_test::constructor_test()
{
    auto ref = source_reference("test.od", 5);
    auto target = std::make_shared<numeric_literal_token>(ref, 42L);
    assert_equal(ref, target->source());
    assert_equal(token::token_type::NUMERIC_LITERAL, target->type());
    assert_equal(42L, target->integer_value());
    assert_equal(true, target->is_integer());

    auto target2 = std::make_shared<numeric_literal_token>(ref, 3.14);
    assert_equal(ref, target2->source());
    assert_equal(token::token_type::NUMERIC_LITERAL, target2->type());
    assert_equal(3.14, target2->double_value());
    assert_equal(false, target2->is_integer());
}

void numeric_literal_token_test::to_string_test()
{
    auto ref = source_reference("test.od", 5);
    auto target = std::make_shared<numeric_literal_token>(ref, 42L);
    assert_equal(std::string("42"), target->to_string());

    auto target2 = std::make_shared<numeric_literal_token>(ref, 3.14);
    assert_equal(std::string("3.14"), target2->to_string());
}