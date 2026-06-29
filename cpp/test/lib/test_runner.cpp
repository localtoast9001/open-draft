/**
 * Copyright (c) 2024 Jon Rowlett. All rights reserved.
 * Licensed under the MIT License. See LICENSE in the project root for license information.
 * @file test_runner.cpp
 * @brief Contains the implementation of the test runner for the test framework.
 */

#include <testfx.hpp>
#include <iostream>
#include <sstream>

namespace testfx
{
    constexpr const char* k_pass_label = "[\x1b[32mPASS\x1b[0m]";
    constexpr const char* k_fail_label = "[\x1b[31mFAIL\x1b[0m]";

    test_runner::test_runner()
        : _test_classes()
    {
        test_class::init_instances(_test_classes);
    }

    test_runner::test_runner(
	        std::initializer_list<test_class*> tests)
    {
        for (auto test : tests)
        {
            _test_classes[test->name()] = test;
        }
    }

    int test_runner::run(int argc, const char* argv[])
    {
        // Implementation for running all registered test classes and their test methods
        test_runner runner;
        
        return runner.run() ? 0 : 1; // Return 0 for success, 1 for failure
    }

    bool test_runner::run()
    {
        test_context context;
        context.init();

        int total_passed = 0;
        int total_failed = 0;

        for (const auto& pair : _test_classes)
        {
            test_class* cls = pair.second;
            cls->init(context);
            test_summary summary;
            run_test_class(*cls, summary);
            total_passed += summary.passed_tests();
            total_failed += summary.failed_tests();

            std::cout << cls->name() << ": "
                << summary.passed_tests() << " passed, "
                << summary.failed_tests() << " failed.\n";

        }

        std::cout << "Total: " << total_passed << " passed, " << total_failed << " failed.\n";

        return total_failed == 0; // Return true if all tests passed, false otherwise
    }

    void test_runner::run_test_class(
        test_class& cls,
        test_summary& summary)
    {
        for (const auto& test_pair : cls.tests())
        {
            const std::string& test_name = test_pair.first;
            test_method method = test_pair.second;

            test_result result;
            auto full_test_name = cls.name() + "::" + test_name;

            run_test_method(cls, test_name, method, result);
            summary.add_result(result);
            if (result.passed())
            {
                std::cout << k_pass_label << " " << full_test_name << " (" << std::chrono::duration_cast<std::chrono::microseconds>(result.duration()).count() << "us)" << std::endl;
            }
            else
            {
                std::cout << k_fail_label << " " << full_test_name << " (" << std::chrono::duration_cast<std::chrono::microseconds>(result.duration()).count() << "us)" << std::endl;
                std::cout << "    " << result.message() << std::endl;
            }
        }
    }

    void test_runner::run_test_method(
        test_class& cls,
        const std::string& test_name,
        test_method method,
        test_result& result)
    {
        // Start timing the test method execution
        auto start_time = std::chrono::high_resolution_clock::now();
        bool test_passed = false;
        std::stringstream failure_message;

        try
        {
            (cls.*method)(); // Call the test method
            test_passed = true;
        }
        catch (const assert_exception& e)
        {
            // Log the assertion failure message
            failure_message << "Test failed: " << e.what();
            failure_message << " at " << e.location().file_name() << ":" << e.location().line() << " in function " << e.location().function_name(); 
        }
        catch (const std::exception& e)
        {
            // Log any other exceptions
            failure_message << "Test failed with exception: " << e.what();
        }

        // Stop timing the test method execution
        auto end_time = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end_time - start_time;
        if (test_passed)
        {
            result.pass(duration);
        }
        else
        {
            result.fail(failure_message.str(), duration);
        }
    }
}