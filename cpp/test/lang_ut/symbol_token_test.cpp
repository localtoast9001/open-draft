/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 * Licensed under the MIT license. See LICENSE file in the project root for full license information.
 * @file symbol_token_test.cpp
 * @brief unit tests for the symbol_token class.
 */
#include <token.hpp>
#include <testfx.hpp>

using namespace testfx;
using namespace opendraft::lang;

class symbol_token_test : public test_class
{
public:
    static symbol_token_test instance;
    symbol_token_test();

    void constructor_test();
    void to_string_test();
};

symbol_token_test symbol_token_test::instance;

symbol_token_test::symbol_token_test()
: test_class("symbol_token_test")
{
    add("constructor_test", (test_method)&symbol_token_test::constructor_test);
    add("to_string_test", (test_method)&symbol_token_test::to_string_test);
}

void symbol_token_test::constructor_test()
{
    auto ref = source_reference("test.od", 5);
    auto target = std::make_shared<symbol_token>(ref, symbol::SYMBOL_LEFT_PAREN);
    assert_equal(ref, target->source());
    assert_equal(token::token_type::SYMBOL, target->type());
    assert_equal(symbol::SYMBOL_LEFT_PAREN, target->value());
}

void symbol_token_test::to_string_test()
{
    auto ref = source_reference("test.od", 5);
    auto target = std::make_shared<symbol_token>(ref, symbol::SYMBOL_LEFT_PAREN);
    assert_equal(std::string("("), target->to_string());
}
