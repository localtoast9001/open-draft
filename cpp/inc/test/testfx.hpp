/**
 * @file testfx.hpp
 * @brief Contains the declarations for the test framework and related functions.
 */
#pragma once

#ifndef _TESTFX_HPP_
#define _TESTFX_HPP_

#include <string>
#include <map>
#include <exception>
#include <chrono>
#include <source_location>

namespace testfx
{
    class test_class;
    class test_runner;
    class test_context;
    class test_result;
    class test_summary;
    class assert_exception;

    /**
     * @brief Type definition for a test method pointer.
     * A test method is a member function of a test class that takes no parameters and returns void.
     * It is used to define individual test cases within a test class.
     */
    typedef void (test_class::*test_method)();

    /**
     * @brief Base class for all test classes.
     */
    class test_class
    {
    public:

        /**
         * @brief Initializes the test class instances and registers them with the test runner.
         * @param instances A map to hold the registered test class instances.
         */
        static void init_instances(std::map<std::string, test_class*>& instances);

        /** 
         * Called by the framework to initialize the test class with the given test context. 
         */
        void init(test_context& context);

        /**
         * @brief Returns the name of the test class.
         * @return The name of the test class.
         */
        const std::string& name() const { return _name; }

        /**
         * @brief Returns the map of test methods associated with the test class.
         * @return A constant reference to the map of test methods.
         */
        const std::map<std::string, test_method>& tests() const { return _tests; }
    protected:
        test_class(const std::string& name);
        virtual ~test_class() = default;

        /**
         * @brief Returns the test context associated with the test class.
         * @return The test context.
         * @throws assert_exception if the test context is not initialized.
         */
        test_context& context() const;

        /**
         * @brief Adds a test method to the test class.
         * @param name The name of the test method.
         * @param method The test method to add.
         */
        void add(const std::string& name, test_method method);

    private:
        static test_class* _head;
        test_class* _next;

        std::string _name;
        std::map<std::string, test_method> _tests;
        test_context* _context;
    };

    /**
     * @brief Exception class for assertion failures in tests.
     */
    class assert_exception : public std::exception
    {
    public:
        explicit assert_exception(
            const std::string& message,
            const std::source_location& location = std::source_location::current());
        const char* what() const noexcept override
        {
            return _message.c_str();
        }

        const std::source_location& location() const noexcept
        {
            return _location;
        }

    private:
        std::string _message;
        std::source_location _location;
    };

    /**
     * @brief The test_context class provides environment metadata and other context info and services for running tests.
     */
    class test_context
    {
    public:
        test_context();
        ~test_context() = default;

        inline const std::string& get_test_run_id() const { return _test_run_id; }
        inline const std::string& get_test_data_path() const { return _test_data_path; }

        void init();

    private:
        std::string _test_run_id;
        std::string _test_data_path;

        test_context(const test_context&) = delete;
        test_context& operator=(const test_context&) = delete;
    };

    /**
     * @brief Class responsible for running all registered test classes and their associated test methods.
     */
    class test_runner
    {
    public:
        test_runner();
        test_runner(
	        std::initializer_list<test_class*> tests);

        virtual ~test_runner() = default;

        /**
         * @brief Runs all registered test classes and their associated test methods.
         * @param argc The number of command-line arguments.
         * @param argv The array of command-line arguments.
         * @return The exit code of the test run.
         */
        static int run(int argc, const char* argv[]);

    private:
        bool run();
        void run_test_class(
            test_class& cls,
            test_summary& summary);

        void run_test_method(
            test_class& cls,
            const std::string& test_name,
            test_method method,
            test_result& result);

        std::map<std::string, test_class*> _test_classes;
    };

    /**
     * @brief Class representing the result of a test method.
     */
    class test_result
    {
    public:
        test_result();
        ~test_result() = default;

        inline bool passed() const { return _passed; }
        inline const std::string& message() const { return _message; }
        inline const std::chrono::duration<double>& duration() const { return _duration; }

        /**
         * @brief Marks the test result as passed.
         * @param duration The duration of the test execution.
         */
        void pass(const std::chrono::duration<double>& duration);
        
        /**
         * @brief Marks the test result as failed.
         * @param message The failure message.
         * @param duration The duration of the test execution.
         */
        void fail(const std::string& message, const std::chrono::duration<double>& duration);
    
    private:
        bool _passed;
        std::string _message;
        std::chrono::duration<double> _duration;
    };

    /**
     * @brief Class representing a summary of test results for a test class.
     */
    class test_summary
    {
    public: 
        test_summary();
        ~test_summary() = default;

        inline int passed_tests() const { return _passed_tests; }
        inline int failed_tests() const { return _failed_tests; }

        void add_result(const test_result& result);

    private:
        int _passed_tests;
        int _failed_tests;
    };

    template<typename T>
    void assert_equal(
        const T& expected,
        const T& actual,
        const std::source_location& location = std::source_location::current())
    {
        if (expected != actual)
        {
            std::ostringstream oss;
            oss << "Assertion failed: expected [" << expected << "], got [" << actual << "]";
            throw assert_exception(oss.str(), location);
        }
    }
}

#endif /* _TESTFX_HPP_ */
