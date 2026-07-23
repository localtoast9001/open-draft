/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 * Licensed under the MIT license. See LICENSE file in the project root for full license information.
 */

#include "token_reader_test_utility.hpp"

using namespace opendraft::lang;
using namespace std;
using namespace testfx;

shared_ptr<token_reader> token_reader_test_utility::create_token_reader(
    std::istream& input,
    test_message_log& log,
    const std::source_location& location)
{
    source_reference start = source_reference::from_source_location(location);
    return make_shared<token_reader>(
        input,
        start,
        [&log](const message& msg) { log.log(msg); });
}

void token_reader_test_utility::single_token_clean_test(
    const std::string& expected_value,
    const std::string& input,
    const std::source_location& location)
{
    test_message_log log;
    std::istringstream ss(input);
    auto reader = create_token_reader(ss, log, location);
    auto token = reader->read();
    assert_not_null(token, location);
    auto type = token->type();
    assert_equal(token::token_type::STRING_LITERAL, type, location);
    auto string_token = static_cast<string_literal_token*>(token.get());
    assert_equal(string(expected_value), string_token->value(), location);
    assert_equal((size_t)0, log.messages().size(), location);
}

void token_reader_test_utility::single_token_clean_test(
    long expected_value,
    const std::string& input,
    const char* expected_units,
    const std::source_location& location)
{
    test_message_log log;
    std::istringstream ss(input);
    auto reader = create_token_reader(ss, log, location);
    auto token = reader->read();
    assert_not_null(token, location);
    auto type = token->type();
    assert_equal(token::token_type::NUMERIC_LITERAL, type, location);
    auto numeric_token = static_cast<numeric_literal_token*>(token.get());
    assert_equal(true, numeric_token->is_integer());
    assert_equal(expected_value, numeric_token->integer_value(), location);

    if (expected_units != nullptr)
    {
        assert_equal(string(expected_units), numeric_token->unit(), location);
    }

    assert_equal((size_t)0, log.messages().size(), location);
}

void token_reader_test_utility::single_token_clean_test(
    double expected_value,
    const std::string& input,
    const char* expected_units,
    const std::source_location& location)
{
    test_message_log log;
    std::istringstream ss(input);
    auto reader = create_token_reader(ss, log, location);
    auto token = reader->read();
    assert_not_null(token, location);
    auto type = token->type();
    assert_equal(token::token_type::NUMERIC_LITERAL, type, location);
    auto numeric_token = static_cast<numeric_literal_token*>(token.get());
    assert_equal(false, numeric_token->is_integer(), location);
    assert_equal(expected_value, numeric_token->double_value(), location);

    if (expected_units != nullptr)
    {
        assert_equal(string(expected_units), numeric_token->unit(), location);
    }

    assert_equal((size_t)0, log.messages().size(), location);
}