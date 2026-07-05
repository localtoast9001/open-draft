/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 * Licensed under the MIT license. See LICENSE file in the project root for full license information.
 * @file identifier_token_test.cpp
 * @brief unit tests for the identifier_token class.
 */
#include <token.hpp>
#include <testfx.hpp>

using namespace testfx;
using namespace opendraft::lang;

class identifier_token_test : public test_class
{
public:
    static identifier_token_test instance;
    identifier_token_test();

    void constructor_test();
    void to_string_test();
};

identifier_token_test identifier_token_test::instance;

identifier_token_test::identifier_token_test()
: test_class("identifier_token_test")
{
    add("constructor_test", (test_method)&identifier_token_test::constructor_test);
    add("to_string_test", (test_method)&identifier_token_test::to_string_test);
}

void identifier_token_test::constructor_test()
{
    auto ref = source_reference("test.od", 5);
    auto target = std::make_shared<identifier_token>(ref, "identifier");
    assert_equal(ref, target->source());
    assert_equal(token::token_type::IDENTIFIER, target->type());
    assert_equal(std::string("identifier"), target->name());
}

void identifier_token_test::to_string_test()
{
    auto ref = source_reference("test.od", 5);
    auto target = std::make_shared<identifier_token>(ref, "identifier");
    assert_equal(std::string("identifier"), target->to_string());
}
