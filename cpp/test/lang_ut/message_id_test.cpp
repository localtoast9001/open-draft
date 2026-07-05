/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 * Licensed under the MIT license. See LICENSE file in the project root for full license information.
 * @file message_id_test.cpp
 * @brief Defines the unit tests for the message_id class.
 */
#include <testfx.hpp>
#include <message.hpp>

using namespace testfx;
using namespace opendraft::lang;

class message_id_test : public test_class
{
public:
    static message_id_test instance;
    message_id_test();

    void default_constructor_test();
    void constructor_with_category_and_code_test();
    void copy_constructor_test();
    void assignment_operator_test();
    void equality_operator_test();
    void to_string_test();

    // negative tests
    void category_length_exceeds_max_test();
    void code_negative_test();
    void code_more_than_9999_test();
};

message_id_test message_id_test::instance;

message_id_test::message_id_test()
: test_class("message_id_test")
{
    add("default_constructor_test", (test_method)&message_id_test::default_constructor_test);
    add("constructor_with_category_and_code_test", (test_method)&message_id_test::constructor_with_category_and_code_test);
    add("copy_constructor_test", (test_method)&message_id_test::copy_constructor_test);
    add("assignment_operator_test", (test_method)&message_id_test::assignment_operator_test);
    add("equality_operator_test", (test_method)&message_id_test::equality_operator_test);
    add("to_string_test", (test_method)&message_id_test::to_string_test);
    add("category_length_exceeds_max_test", (test_method)&message_id_test::category_length_exceeds_max_test);
    add("code_negative_test", (test_method)&message_id_test::code_negative_test);
    add("code_more_than_9999_test", (test_method)&message_id_test::code_more_than_9999_test);
}

void message_id_test::default_constructor_test()
{
    message_id id;
    assert_equal(std::string_view(""), id.category());
    assert_equal(0, id.code());
}

void message_id_test::constructor_with_category_and_code_test()
{
    message_id id("TEST", 42);
    assert_equal(std::string_view("TEST"), id.category());
    assert_equal(42, id.code());
}

void message_id_test::copy_constructor_test()
{
    message_id original("COPY", 99);
    message_id copy(original);
    assert_equal(original.category(), copy.category());
    assert_equal(original.code(), copy.code());
}

void message_id_test::assignment_operator_test()
{
    message_id original("AS", 123);
    message_id assigned;
    assigned = original;
    assert_equal(original.category(), assigned.category());
    assert_equal(original.code(), assigned.code());
}

void message_id_test::equality_operator_test()
{
    message_id id1("EQ", 1);
    message_id id2("EQ", 1);
    message_id id3("NEQ", 2);

    assert_equal(true, id1 == id2);
    assert_equal(false, id1 == id3);
}

void message_id_test::to_string_test()
{
    message_id id("TEST", 456);
    assert_equal(std::string("TEST0456"), id.to_string());
}

void message_id_test::category_length_exceeds_max_test()
{
    message_id id("TOOLONG", 1);
    assert_equal(std::string_view("TOOL"), id.category());
}

void message_id_test::code_negative_test()
{
    message_id id("NEG", -1);
    assert_equal(-1, id.code());
    assert_equal(std::string("NEG-001"), id.to_string());
}

void message_id_test::code_more_than_9999_test()
{
    message_id id("BIG", 10000);
    assert_equal(10000, id.code());
    assert_equal(std::string("BIG1000"), id.to_string());
}