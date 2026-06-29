/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 * Licensed under the MIT license. See LICENSE file in the project root for full license information.
 */

#include <testfx.hpp>
#include <source_reference.hpp>

using namespace testfx;
using namespace opendraft::lang;

/**
 * @brief A test class for testing source reference functionality.
 */
class source_reference_test : public test_class
{
public:
    static source_reference_test instance;
    source_reference_test();

    void default_constructor_test();
    void constructor_with_path_test();
    void constructor_with_path_and_line_test();
    void constructor_with_path_line_and_column_test();
    void constructor_with_path_line_column_endline_endcolumn_test();
    void to_string_default_test();
    void to_string_with_path_test();
    void to_string_with_path_and_line_test();
    void to_string_with_path_line_and_column_test();
    void to_string_with_path_line_column_endline_endcolumn_test();
    void to_string_with_path_line_endline_test();
};

source_reference_test source_reference_test::instance;

source_reference_test::source_reference_test()
    : test_class("source_reference_test")
{
    add("default_constructor_test", (test_method)&source_reference_test::default_constructor_test);
    add("constructor_with_path_test", (test_method)&source_reference_test::constructor_with_path_test);
    add("constructor_with_path_and_line_test", (test_method)&source_reference_test::constructor_with_path_and_line_test);
    add("constructor_with_path_line_and_column_test", (test_method)&source_reference_test::constructor_with_path_line_and_column_test);
    add("constructor_with_path_line_column_endline_endcolumn_test", (test_method)&source_reference_test::constructor_with_path_line_column_endline_endcolumn_test);
    add("to_string_default_test", (test_method)&source_reference_test::to_string_default_test);
    add("to_string_with_path_test", (test_method)&source_reference_test::to_string_with_path_test);
    add("to_string_with_path_and_line_test", (test_method)&source_reference_test::to_string_with_path_and_line_test);
    add("to_string_with_path_line_and_column_test", (test_method)&source_reference_test::to_string_with_path_line_and_column_test);
    add("to_string_with_path_line_column_endline_endcolumn_test", (test_method)&source_reference_test::to_string_with_path_line_column_endline_endcolumn_test);
    add("to_string_with_path_line_endline_test", (test_method)&source_reference_test::to_string_with_path_line_endline_test);
}

void source_reference_test::default_constructor_test()
{
    source_reference ref;
    assert_equal(std::string(), ref.path());
    assert_equal(0, ref.line());
    assert_equal(0, ref.column());
    assert_equal(0, ref.end_line());
    assert_equal(0, ref.end_column());
}

void source_reference_test::constructor_with_path_test()
{
    source_reference ref("test.cpp");
    assert_equal(std::string("test.cpp"), ref.path());
    assert_equal(0, ref.line());
    assert_equal(0, ref.column());
    assert_equal(0, ref.end_line());
    assert_equal(0, ref.end_column());
}

void source_reference_test::constructor_with_path_and_line_test()
{
    source_reference ref("test.cpp", 10);
    assert_equal(std::string("test.cpp"), ref.path());
    assert_equal(10, ref.line());
    assert_equal(0, ref.column());
    assert_equal(10, ref.end_line());
    assert_equal(0, ref.end_column());
}

void source_reference_test::constructor_with_path_line_and_column_test()
{
    source_reference ref("test.cpp", 10, 5);
    assert_equal(std::string("test.cpp"), ref.path());
    assert_equal(10, ref.line());
    assert_equal(5, ref.column());
    assert_equal(10, ref.end_line());
    assert_equal(5, ref.end_column());
}

void source_reference_test::constructor_with_path_line_column_endline_endcolumn_test()
{
    source_reference ref("test.cpp", 10, 5, 12, 8);
    assert_equal(std::string("test.cpp"), ref.path());
    assert_equal(10, ref.line());
    assert_equal(5, ref.column());
    assert_equal(12, ref.end_line());
    assert_equal(8, ref.end_column());
}

void source_reference_test::to_string_default_test()
{
    source_reference ref;
    assert_equal(std::string(""), ref.to_string());
}

void source_reference_test::to_string_with_path_test()
{
    source_reference ref("test.cpp");
    assert_equal(std::string("test.cpp"), ref.to_string());
}

void source_reference_test::to_string_with_path_and_line_test()
{
    source_reference ref("test.cpp", 10);
    assert_equal(std::string("test.cpp:10"), ref.to_string());
}

void source_reference_test::to_string_with_path_line_and_column_test()
{
    source_reference ref("test.cpp", 10, 5);
    assert_equal(std::string("test.cpp:10:5"), ref.to_string());
}

void source_reference_test::to_string_with_path_line_column_endline_endcolumn_test()
{
    source_reference ref("test.cpp", 10, 5, 12, 8);
    assert_equal(std::string("test.cpp:10:5-12:8"), ref.to_string());
}

void source_reference_test::to_string_with_path_line_endline_test()
{
    source_reference ref("test.cpp", 10, 0, 12, 0);
    assert_equal(std::string("test.cpp:10-12"), ref.to_string());
}
