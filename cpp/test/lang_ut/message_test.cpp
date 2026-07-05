/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 * Licensed under the MIT license. See LICENSE file in the project root for full license information.
 * @file message_test.cpp
 * @brief Defines the unit tests for the message class.
 */
#include <testfx.hpp>
#include <message.hpp>

using namespace testfx;
using namespace opendraft::lang;

class message_test : public test_class
{
public:
    static message_test instance;
    message_test();

    void default_constructor_test();
    void constructor_test();
    void copy_constructor_test();
    void assignment_operator_test();
    void to_string_test();
    void default_to_string_test();
};

message_test message_test::instance;

message_test::message_test()
: test_class("message_test")
{
    add("default_constructor_test", (test_method)&message_test::default_constructor_test);
    add("constructor_test", (test_method)&message_test::constructor_test);
    add("copy_constructor_test", (test_method)&message_test::copy_constructor_test);
    add("assignment_operator_test", (test_method)&message_test::assignment_operator_test);
    add("to_string_test", (test_method)&message_test::to_string_test);
    add("default_to_string_test", (test_method)&message_test::default_to_string_test);
}

void message_test::default_constructor_test()
{
    message msg;
    assert_equal(std::string(), msg.source().path());
    assert_equal(0, msg.source().line());
    assert_equal(0, msg.source().column());
    assert_equal(0, msg.source().end_line());
    assert_equal(0, msg.source().end_column());
    assert_equal(std::string_view(""), msg.id().category());
    assert_equal(0, msg.id().code());
    assert_equal(SEVERITY_ERROR, msg.severity());
    assert_equal(std::string(), msg.text());
}

void message_test::constructor_test()
{
    source_reference source("test.cpp", 1, 2, 3, 4);
    message_id id("TEST", 42);
    message msg(source, id, SEVERITY_ERROR, "This is a test message.");
    assert_equal(source.path(), msg.source().path());
    assert_equal(source.line(), msg.source().line());
    assert_equal(source.column(), msg.source().column());
    assert_equal(source.end_line(), msg.source().end_line());
    assert_equal(source.end_column(), msg.source().end_column());
    assert_equal(id.category(), msg.id().category());
    assert_equal(id.code(), msg.id().code());
    assert_equal(SEVERITY_ERROR, msg.severity());
    assert_equal(std::string("This is a test message."), msg.text());
}

void message_test::copy_constructor_test()
{
    source_reference source("test.cpp", 1, 2, 3, 4);
    message_id id("TEST", 42);
    message msg(source, id, SEVERITY_ERROR, "This is a test message.");
    message copy(msg);
    assert_equal(msg.source().path(), copy.source().path());
    assert_equal(msg.source().line(), copy.source().line());
    assert_equal(msg.source().column(), copy.source().column());
    assert_equal(msg.source().end_line(), copy.source().end_line());
    assert_equal(msg.source().end_column(), copy.source().end_column());
    assert_equal(msg.id().category(), copy.id().category());
    assert_equal(msg.id().code(), copy.id().code());
    assert_equal(msg.severity(), copy.severity());
    assert_equal(msg.text(), copy.text());
}

void message_test::assignment_operator_test()
{
    source_reference source("test.cpp", 1, 2, 3, 4);
    message_id id("TEST", 42);
    message msg(source, id, SEVERITY_ERROR, "This is a test message.");
    message copy = msg;
    assert_equal(msg.source().path(), copy.source().path());
    assert_equal(msg.source().line(), copy.source().line());
    assert_equal(msg.source().column(), copy.source().column());
    assert_equal(msg.source().end_line(), copy.source().end_line());
    assert_equal(msg.source().end_column(), copy.source().end_column());
    assert_equal(msg.id().category(), copy.id().category());
    assert_equal(msg.id().code(), copy.id().code());
    assert_equal(msg.severity(), copy.severity());
    assert_equal(msg.text(), copy.text());
}

void message_test::to_string_test()
{
    source_reference source("test.cpp", 1, 2, 3, 4);
    message_id id("TEST", 42);
    message msg(source, id, SEVERITY_ERROR, "This is a test message.");
    std::string expected = "test.cpp:1:2-3:4: error: TEST0042: This is a test message.";
    assert_equal(expected, msg.to_string());
}

void message_test::default_to_string_test()
{
    message msg;
    std::string expected = ": error: 0000: ";
    assert_equal(expected, msg.to_string());
}