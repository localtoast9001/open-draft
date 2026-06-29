/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 * Licensed under the MIT license. See LICENSE file in the project root for full license information.
 * @file test_context.cpp
 * @brief Contains the implementation of the test_context class.
 */
#include <testfx.hpp>
#include <array>
#include <ctime>
#include <filesystem>
#include <unistd.h>
#include <iostream>

namespace testfx
{
    std::filesystem::path get_executable_path()
    {
        std::filesystem::path executable_path;
        std::array<char, 4096> buffer{};
        const ssize_t length = readlink("/proc/self/exe", buffer.data(), buffer.size() - 1);
        if (length > 0)
        {
            buffer[static_cast<size_t>(length)] = '\0';
            executable_path = std::filesystem::path(buffer.data());
        }

        return executable_path;
    }

    test_context::test_context()
        : _test_run_id(), _test_data_path()
    {
    }

    void test_context::init()
    {
        std::filesystem::path executable_path = get_executable_path();

        std::string executable_name = executable_path.filename().string();
        if (executable_name.empty())
        {
            executable_name = "unknown";
        }

        // create a unique test run ID based on the current time and name of the program executable.
        _test_run_id = executable_name + "_" + std::to_string(std::time(nullptr));

        // create a test data path based on the run id and the location of the test executable.
        std::filesystem::path base_path = executable_path.parent_path();
        if (base_path.empty())
        {
            base_path = std::filesystem::path("test_data");
        }
        else
        {
            base_path /= "test_data";
        }

        // create the test data path if it doesn't exist
        std::error_code ec;
        base_path /= _test_run_id;
        std::filesystem::create_directories(base_path, ec);
        if (ec)
        {
            std::cerr << "Failed to create test data directory: " << base_path << ", error: " << ec.message() << std::endl;
        }

        _test_data_path = base_path.string() + "/";
    }
}