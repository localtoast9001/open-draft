/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 * Licensed under the MIT license. See LICENSE file in the project root for full license information.
 * @file token_reader_test.cpp
 * @brief unit tests for the token_reader class.
 */
#include <token_reader.hpp>
#include <testfx.hpp>
#include <sstream>
#include <iostream>

using namespace testfx;
using namespace opendraft::lang;

/**
 * @brief Test class for the token_reader class.
 */
class token_reader_test : public test_class
{
public:
    static token_reader_test instance;
    token_reader_test();

    void constructor_test();
};

token_reader_test token_reader_test::instance;

token_reader_test::token_reader_test()
: test_class("token_reader_test")
{
    add("constructor_test", (test_method)&token_reader_test::constructor_test);
}

void token_reader_test::constructor_test()
{
    std::istringstream input("test input");
    source_reference start_source("test.od", 1, 1);
    auto message_callback = [](const message& msg) {
        std::cout << msg.to_string() << std::endl;
    };

    token_reader reader(input, start_source, message_callback);

    assert_equal(start_source, reader.current_source());
}