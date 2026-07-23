/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 * Licensed under the MIT license. See LICENSE file in the project root for full license information.
 */

#pragma once
#ifndef __TOKEN_READER_TEST_UTILITY_H__
#define __TOKEN_READER_TEST_UTILITY_H__

#include <testfx.hpp>
#include <token_reader.hpp>
#include "test_message_log.hpp"

/**
 * Helper methods used by tests for token_reader.
 */
class token_reader_test_utility
{
public:
    /**
     * @brief Creates a token reader from string input.
     * @param input The input string to read tokens from.
     * @param log The message log to record any messages.
     * @param location The source location for error reporting.
     */
    static std::shared_ptr<opendraft::lang::token_reader> create_token_reader(
        std::istream& input,
        test_message_log& log,
        const std::source_location& location = std::source_location::current());

    /**
     * @brief Tests that a single token is correctly read from the input string.
     * @param expected_value The expected value of the token.
     * @param input The input string to read the token from.
     * @param location The source location for error reporting.
     */
    static void single_token_clean_test(
        const std::string& expected_value,
        const std::string& input,
        const std::source_location& location = std::source_location::current());

    /**
     * @brief Tests that a single token is correctly read from the input string.
     * @param expected_value The expected value of the token.
     * @param input The input string to read the token from.
     * @param expected_units The expected units of the token.
     * @param location The source location for error reporting.
     */
    static void single_token_clean_test(
        long expected_value,
        const std::string& input,
        const char* expected_units = nullptr,
        const std::source_location& location = std::source_location::current());
    
    /**
     * @brief Tests that a single token is correctly read from the input string.
     * @param expected_value The expected value of the token.
     * @param input The input string to read the token from.
     * @param expected_units The expected units of the token.
     * @param location The source location for error reporting.
     */
    static void single_token_clean_test(
        double expected_value,
        const std::string& input,
        const char* expected_units = nullptr,
        const std::source_location& location = std::source_location::current());

private:
    token_reader_test_utility() = delete;
};

#endif /* __TOKEN_READER_TEST_UTILITY_H__ */