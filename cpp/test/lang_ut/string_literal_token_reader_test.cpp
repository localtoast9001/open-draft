/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 * Licensed under the MIT license. See LICENSE file in the project root for full license information.
 */

#include <testfx.hpp>
#include <token_reader.hpp>
#include "token_reader_test_utility.hpp"

using namespace opendraft::lang;
using namespace testfx;

class string_literal_token_reader_test : public test_class
{
public:
    static string_literal_token_reader_test instance;

    string_literal_token_reader_test();

    void empty_string_test();
    void basic_string_test();
    void escaped_string_test();
    void emoji_string_test();
    void hebrew_string_test();
    void arabic_string_test();
    void traditional_chinese_string_test();
    void simplified_chinese_string_test();
    void japanese_string_test();
    void korean_string_test();
    void escape_sequence_test();
    void all_escape_sequence_test();
    void hexadecimal_escape_sequence_test();
    void utf8_hex_escape_sequence_test();
    void single_digit_hex_escape_sequence_test();
    void embedded_null_character_test();
    void mixed_case_hex_escape_sequence_test();
    void read_with_unterminated_string_logs_message_and_returns_null();
    void read_with_newline_in_string_logs_message_and_returns_null();
    void read_invalid_escape_sequence_logs_message_and_returns_null();
    void read_invalid_hex_escape_sequence_logs_message_and_returns_null();
    void read_end_of_string_in_hex_escape_sequence_logs_message_and_returns_null();
};

string_literal_token_reader_test string_literal_token_reader_test::instance;

string_literal_token_reader_test::string_literal_token_reader_test()
: test_class("string_literal_token_reader_test")
{
    add("empty_string_test", (test_method)&string_literal_token_reader_test::empty_string_test);
    add("basic_string_test", (test_method)&string_literal_token_reader_test::basic_string_test);
    add("escaped_string_test", (test_method)&string_literal_token_reader_test::escaped_string_test);
    add("emoji_string_test", (test_method)&string_literal_token_reader_test::emoji_string_test);
    add("hebrew_string_test", (test_method)&string_literal_token_reader_test::hebrew_string_test);
    add("arabic_string_test", (test_method)&string_literal_token_reader_test::arabic_string_test);
    add("traditional_chinese_string_test", (test_method)&string_literal_token_reader_test::traditional_chinese_string_test);
    add("simplified_chinese_string_test", (test_method)&string_literal_token_reader_test::simplified_chinese_string_test);
    add("japanese_string_test", (test_method)&string_literal_token_reader_test::japanese_string_test);
    add("korean_string_test", (test_method)&string_literal_token_reader_test::korean_string_test);
    add("escape_sequence_test", (test_method)&string_literal_token_reader_test::escape_sequence_test);
    add("all_escape_sequence_test", (test_method)&string_literal_token_reader_test::all_escape_sequence_test);
    add("hexadecimal_escape_sequence_test", (test_method)&string_literal_token_reader_test::hexadecimal_escape_sequence_test);
    add("utf8_hex_escape_sequence_test", (test_method)&string_literal_token_reader_test::utf8_hex_escape_sequence_test);
    add("single_digit_hex_escape_sequence_test", (test_method)&string_literal_token_reader_test::single_digit_hex_escape_sequence_test);
    add("embedded_null_character_test", (test_method)&string_literal_token_reader_test::embedded_null_character_test);
    add("mixed_case_hex_escape_sequence_test", (test_method)&string_literal_token_reader_test::mixed_case_hex_escape_sequence_test);
    add("read_with_unterminated_string_logs_message_and_returns_null", (test_method)&string_literal_token_reader_test::read_with_unterminated_string_logs_message_and_returns_null);
    add("read_with_newline_in_string_logs_message_and_returns_null", (test_method)&string_literal_token_reader_test::read_with_newline_in_string_logs_message_and_returns_null);
    add("read_invalid_escape_sequence_logs_message_and_returns_null", (test_method)&string_literal_token_reader_test::read_invalid_escape_sequence_logs_message_and_returns_null);
    add("read_invalid_hex_escape_sequence_logs_message_and_returns_null", (test_method)&string_literal_token_reader_test::read_invalid_hex_escape_sequence_logs_message_and_returns_null);
    add("read_end_of_string_in_hex_escape_sequence_logs_message_and_returns_null", (test_method)&string_literal_token_reader_test::read_end_of_string_in_hex_escape_sequence_logs_message_and_returns_null);
}

void string_literal_token_reader_test::empty_string_test()
{
    token_reader_test_utility::single_token_clean_test(
        "",
        "\"\"");
}

void string_literal_token_reader_test::basic_string_test()
{
    token_reader_test_utility::single_token_clean_test(
        "Hello, World!",
        "\"Hello, World!\"");
}

void string_literal_token_reader_test::escaped_string_test()
{
    token_reader_test_utility::single_token_clean_test(
        "Hello, \"World\"!",
        "\"Hello, \\\"World\\\"!\"");
}

void string_literal_token_reader_test::emoji_string_test()
{
    token_reader_test_utility::single_token_clean_test(
        "Hello, 🌍!",
        "\"Hello, 🌍!\"");    
}

void string_literal_token_reader_test::hebrew_string_test()
{
    token_reader_test_utility::single_token_clean_test(
        "שלום עולם",
        "\"שלום עולם\"");
}

void string_literal_token_reader_test::arabic_string_test()
{
    token_reader_test_utility::single_token_clean_test(
        "مرحبا بالعالم",
        "\"مرحبا بالعالم\"");
}

void string_literal_token_reader_test::traditional_chinese_string_test()
{
    token_reader_test_utility::single_token_clean_test(
        "屙屎屙飯",
        "\"屙屎屙飯\"");
}

void string_literal_token_reader_test::simplified_chinese_string_test()
{
    token_reader_test_utility::single_token_clean_test(
        "吃屎",
        "\"吃屎\"");
}

void string_literal_token_reader_test::japanese_string_test()
{
    token_reader_test_utility::single_token_clean_test(
        "うんこを食べる",
        "\"うんこを食べる\"");
}

void string_literal_token_reader_test::korean_string_test()
{
    token_reader_test_utility::single_token_clean_test(
        "똥을 먹다",
        "\"똥을 먹다\"");
}

void string_literal_token_reader_test::escape_sequence_test()
{
    token_reader_test_utility::single_token_clean_test(
        "Hello, \"World\"!\nNew line.",
        "\"Hello, \\\"World\\\"!\\nNew line.\"");
}

void string_literal_token_reader_test::all_escape_sequence_test()
{
    token_reader_test_utility::single_token_clean_test(
        "\a\b\f\n\r\t\v\\\"",
        "\"\\a\\b\\f\\n\\r\\t\\v\\\\\\\"\"");
}

void string_literal_token_reader_test::hexadecimal_escape_sequence_test()
{
    token_reader_test_utility::single_token_clean_test(
        "Hello, World! \x41\x42\x43",
        "\"Hello, World! \\x41\\x42\\x43\"");
}

void string_literal_token_reader_test::utf8_hex_escape_sequence_test()
{
    token_reader_test_utility::single_token_clean_test(
        "🤡🌎",
        "\"\\xF0\\x9F\\xA4\\xA1\\xF0\\x9F\\x8C\\x8E\"");
}

void string_literal_token_reader_test::single_digit_hex_escape_sequence_test()
{
    token_reader_test_utility::single_token_clean_test(
        "Hello, World! \x0A",
        "\"Hello, World! \\xA\"");
}

void string_literal_token_reader_test::embedded_null_character_test()
{
    token_reader_test_utility::single_token_clean_test(
        std::string("Hello, World! \0", 15),
        "\"Hello, World! \\x00\"");
}

void string_literal_token_reader_test::mixed_case_hex_escape_sequence_test()
{
    token_reader_test_utility::single_token_clean_test(
        "Hello, World! \x0A\x0A\x0A\x0A",
        "\"Hello, World! \\xA\\xa\\x0a\\x0A\"");
}

void string_literal_token_reader_test::read_with_unterminated_string_logs_message_and_returns_null()
{
    message m;
    std::istringstream input("\"unterminated");
    token_reader reader(
        input,
        source_reference("test", 1, 1), 
        [&](const message& msg) { m = msg; });

    auto token = reader.read();
    assert_equal(false, (bool)token);
    assert_equal(opendraft::lang::severity::SEVERITY_ERROR, m.severity());
    assert_equal(std::string("ODL1000"), m.id().to_string());
    assert_equal("unterminated string literal", m.text().c_str());
}

void string_literal_token_reader_test::read_with_newline_in_string_logs_message_and_returns_null()
{
    message m;
    std::istringstream input("\"unterminated\n");
    token_reader reader(
        input,
        source_reference("test", 1, 1), 
        [&](const message& msg) { m = msg; });

    auto token = reader.read();
    assert_equal(false, (bool)token);
    assert_equal(opendraft::lang::severity::SEVERITY_ERROR, m.severity());
    assert_equal(std::string("ODL1000"), m.id().to_string());
    assert_equal("unterminated string literal", m.text().c_str());
}

void string_literal_token_reader_test::read_invalid_escape_sequence_logs_message_and_returns_null()
{
    message m;
    std::istringstream input("\"invalid\\escape\"");
    token_reader reader(
        input,
        source_reference("test", 1, 1), 
        [&](const message& msg) { m = msg; });

    auto token = reader.read();
    assert_equal(false, (bool)token);
    assert_equal(opendraft::lang::severity::SEVERITY_ERROR, m.severity());
    assert_equal(std::string("ODL1003"), m.id().to_string());
    assert_equal("unknown escape sequence", m.text().c_str());
}

void string_literal_token_reader_test::read_invalid_hex_escape_sequence_logs_message_and_returns_null()
{
    message m;
    std::istringstream input("\"invalid\\xG\"");
    token_reader reader(
        input,
        source_reference("test", 1, 1), 
        [&](const message& msg) { m = msg; });

    auto token = reader.read();
    assert_equal(false, (bool)token);
    assert_equal(opendraft::lang::severity::SEVERITY_ERROR, m.severity());
    assert_equal(std::string("ODL1004"), m.id().to_string());
    assert_equal("invalid hex escape sequence", m.text().c_str());
}

void string_literal_token_reader_test::read_end_of_string_in_hex_escape_sequence_logs_message_and_returns_null()
{
    message m;
    std::istringstream input("\"unterminated\\x\"");
    token_reader reader(
        input,
        source_reference("test", 1, 1), 
        [&](const message& msg) { m = msg; });

    auto token = reader.read();
    assert_equal(false, (bool)token);
    assert_equal(opendraft::lang::severity::SEVERITY_ERROR, m.severity());
    assert_equal(std::string("ODL1004"), m.id().to_string());
    assert_equal("invalid hex escape sequence", m.text().c_str());
}