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
#include <memory>
#include <functional>
#include <list>

namespace testfx
{
    class test_class;
    class test_runner;
    class test_runner_options;
    class test_report_writer;
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

    typedef std::function<void(test_class&)> test_method_func;

    /**
     * @brief Base class for all test classes.
     */
    class test_class
    {
    public:

        /** 
         * Called by the framework to initialize the test class with the given test context.
         * Override this method to use the test context to register dynamic test methods or set up test data. 
         */
        virtual void init(test_context& context);

        /**
         * @brief Returns the name of the test class.
         * @return The name of the test class.
         */
        const std::string& name() const { return _name; }

        /**
         * @brief Returns the map of test methods associated with the test class.
         * @return A constant reference to the map of test methods.
         */
        const std::map<std::string, test_method_func>& tests() const { return _tests; }

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

        /**
         * @brief Adds a test method to the test class using a function object.
         * @param name The name of the test method.
         * @param method The function object representing the test method.
         */
        void add(const std::string& name, test_method_func method);

    private:
        /**
         * Access to test_runner to call init_instances() to register test_class instances with the test_runner.
         */
        friend class test_runner;

        static test_class* _head;
        test_class* _next;

        std::string _name;
        std::map<std::string, test_method_func> _tests;
        test_context* _context;

        /**
         * @brief Initializes the test class instances and registers them with the test runner.
         * @param instances A map to hold the registered test class instances.
         */
        static void init_instances(std::map<std::string, test_class*>& instances);
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
        inline const std::string& get_test_program_dir_path() const { return _test_program_dir_path; }

        void init();

    private:
        std::string _test_run_id;
        std::string _test_data_path;
        std::string _test_program_dir_path;

        test_context(const test_context&) = delete;
        test_context& operator=(const test_context&) = delete;
    };

    /**
     * @brief Class representing options for the test runner.
     */
    class test_runner_options
    {
    public:
        test_runner_options();
        ~test_runner_options() = default;

        /**
         * @brief Initializes the test runner options based on command-line arguments.
         * @param argc The number of command-line arguments.
         * @param argv The array of command-line arguments.
         * @return True if initialization was successful, false otherwise.
         */
        bool init(int argc, const char* argv[]);

        inline const std::function<std::shared_ptr<test_report_writer>()>& report_writer_factory() const { return _report_writer_factory; }

        inline void report_writer_factory(const std::function<std::shared_ptr<test_report_writer>()>& report_writer_factory) { _report_writer_factory = report_writer_factory; }
    private:
        std::function<std::shared_ptr<test_report_writer>()> _report_writer_factory;

        // disable copy semantics
        test_runner_options(const test_runner_options&) = delete;
        test_runner_options& operator=(const test_runner_options&) = delete;
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

        /**
         * @brief Retrieves the test runner options.
         * @return A reference to the test runner options.
         */
        inline test_runner_options& options() { return _options; }

        /**
         * @brief Retrieves the test runner options as a const reference.
         * @return A const reference to the test runner options.
         */
        inline const test_runner_options& coptions() const { return _options; }

    private:
        bool run();
        void run_test_class(
            test_class& cls,
            test_summary& summary);

        void run_test_method(
            test_class& cls,
            const std::string& test_name,
            const test_method_func& method,
            test_result& result);

        test_runner_options _options;
        std::map<std::string, test_class*> _test_classes;

        // disable copy semantics
        test_runner(const test_runner&) = delete;
        test_runner& operator=(const test_runner&) = delete;
    };

    /**
     * @brief Class representing the result of a test method.
     */
    class test_result
    {
    public:
        test_result(const std::string& name);
        test_result(const test_result& copy) = default;
        test_result(test_result&& move) noexcept = default;
        ~test_result() = default;

        inline bool passed() const { return _passed; }
        inline const std::string& message() const { return _message; }
        inline const std::chrono::duration<double>& duration() const { return _duration; }
        inline const std::string& name() const { return _name; }

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
    
        test_result& operator=(const test_result& copy) = default;
        test_result& operator=(test_result&& move) noexcept = default;

    private:
        std::string _name;
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
        test_summary(const std::string& class_name);
        test_summary(const test_summary& copy) = default;
        test_summary(test_summary&& move) noexcept = default;
        ~test_summary() = default;

        inline const std::string& class_name() const { return _class_name; }
        inline int passed_tests() const { return _passed_tests; }
        inline int failed_tests() const { return _failed_tests; }
        inline const std::chrono::duration<double>& total_duration() const { return _total_duration; }
        inline const std::list<test_result>& results() const { return _results; }

        void add_result(const test_result& result);

        test_summary& operator=(const test_summary& copy) = default;
        test_summary& operator=(test_summary&& move) noexcept = default;

    private:
        std::string _class_name;
        int _passed_tests;
        int _failed_tests;
        std::chrono::duration<double> _total_duration;
        std::list<test_result> _results;
    };

    /**
     * @brief Abstract base class for writing test reports.
     */
    class test_report_writer
    {
    public:
        virtual ~test_report_writer() = default;

        /**
         * @brief Starts the test report file.
         */
        virtual void start_report() = 0;

        /**
         * @brief Ends the test report file.
         */
        virtual void end_report() = 0;

        /**
         * @brief Writes the test summary to the report.
         * @param summary The test summary to write to the report.
         * @note The implementation will interpret the summary information and translate it into the report format.
         */
        virtual void write(const test_summary& summary) = 0;

    protected:
        test_report_writer() = default;

    private:
        // disable copy semantics
        test_report_writer(const test_report_writer&) = delete;
        test_report_writer& operator=(const test_report_writer&) = delete;
    };

    /**
     * @brief Creates a blank test report writer.
     * @return A shared pointer to the created test report writer.
     */
    std::shared_ptr<test_report_writer> create_blank_report_writer();

    /**
     * @brief Creates a JUnit test report writer.
     * @param path The file path for the JUnit report.
     * @return A shared pointer to the created test report writer.
     */
    std::shared_ptr<test_report_writer> create_junit_report_writer(const std::string& path);

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

    template<>
    void assert_equal<double>(
        const double& expected,
        const double& actual,
        const std::source_location& location);

    template<>
    void assert_equal<std::string>(
        const std::string& expected,
        const std::string& actual,
        const std::source_location& location);

    void assert_equal(
        const char* expected,
        const char* actual,
        const std::source_location& location = std::source_location::current());

    template<typename T>
    void assert_not_null(
        const T* ptr,
        const std::source_location& location = std::source_location::current())
    {
        if (ptr == nullptr)
        {
            std::ostringstream oss;
            oss << "Assertion failed: pointer is null";
            throw assert_exception(oss.str(), location);
        }
    }

    template<typename T>
    void assert_not_null(
        const std::shared_ptr<T>& ptr,
        const std::source_location& location = std::source_location::current())
    {
        if (!ptr)
        {
            std::ostringstream oss;
            oss << "Assertion failed: shared pointer is null";
            throw assert_exception(oss.str(), location);
        }
    }
}

#endif /* _TESTFX_HPP_ */
