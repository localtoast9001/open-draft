/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 * Licensed under the MIT license. See LICENSE file in the project root for full license information.
 * @file comment_token_test.cpp
 * @brief unit tests for the comment_token class.
 */
#include <token.hpp>
#include <testfx.hpp>

using namespace testfx;
using namespace opendraft::lang;

/**
 * @brief unit tests for the comment_token class.
 */
class comment_token_test : public test_class
{
public:
    static comment_token_test instance;

    comment_token_test();

    void constructor_test();
    void to_string_test();
};

comment_token_test comment_token_test::instance;

comment_token_test::comment_token_test()
: test_class("comment_token_test")
{
    add("constructor_test", (test_method)&comment_token_test::constructor_test);
    add("to_string_test", (test_method)&comment_token_test::to_string_test);
}

void comment_token_test::constructor_test()
{
    auto ref = source_reference("test.od", 5);
    auto target = std::make_shared<comment_token>(ref, "comment");
    assert_equal(ref, target->source());
    assert_equal(token::token_type::COMMENT, target->type());
    assert_equal(std::string("comment"), target->text());
}

void comment_token_test::to_string_test()
{
    auto ref = source_reference("test.od", 5);
    auto target = std::make_shared<comment_token>(ref, "comment");
    assert_equal(std::string("/* comment */"), target->to_string());
}