/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 * Licensed under the MIT license. See LICENSE file in the project root for full license information.
 * @file keyword_token_test.cpp
 * @brief unit tests for the keyword_token class.
 */
#include <token.hpp>
#include <testfx.hpp>

using namespace testfx;
using namespace opendraft::lang;

class keyword_token_test : public test_class
{
public:
    static keyword_token_test instance;
    keyword_token_test();

    void constructor_test();
    void to_string_test();
};

keyword_token_test keyword_token_test::instance;

keyword_token_test::keyword_token_test()
: test_class("keyword_token_test")
{
    add("constructor_test", (test_method)&keyword_token_test::constructor_test);
    add("to_string_test", (test_method)&keyword_token_test::to_string_test);
}

void keyword_token_test::constructor_test()
{
    auto ref = source_reference("test.od", 5);
    auto target = std::make_shared<keyword_token>(ref, keyword::KEYWORD_IF);
    assert_equal(ref, target->source());
    assert_equal(token::token_type::KEYWORD, target->type());
    assert_equal(keyword::KEYWORD_IF, target->value());
}

void keyword_token_test::to_string_test()
{
    auto ref = source_reference("test.od", 5);
    auto target = std::make_shared<keyword_token>(ref, keyword::KEYWORD_IF);
    assert_equal(std::string("if"), target->to_string());
}