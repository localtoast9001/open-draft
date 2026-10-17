/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 * @file junit_test_report_writer.cpp
 * @brief Implementation of the junit_test_report_writer class.
 */
#include "testfx.hpp"
#include <fstream>
#include <xml_writer.hpp>

using namespace testfx;
using namespace std;
using namespace xml;

/**
 * @brief Writes test results in the JUnit report format.
 * @note JUnit schema:
 * @note <testsuites>: The root element aggregating all test suites.
 * @note <testsuite>: Represents a single test suite (often corresponding to a class or file), 
 * @note containing attributes like name, tests (total count), failures, errors, and time. 
 * @note <testcase>: Represents an individual test execution, 
 * @note with attributes like name, classname, time, and status.
 * @note Within test cases, specific elements detail the outcome:
 * @note <failure>: Indicates a test failed, containing a message and stack trace.
 * @note <error>: Indicates a test encountered an exception or error.
 * @note <skipped>: Indicates a test was skipped. 
 * @note <system-out>: Captures standard output produced during the test execution.
 * @note <system-err>: Captures standard error output produced during the test execution.
 */
class junit_test_report_writer : public test_report_writer
{
public:
    junit_test_report_writer(const string& path);
    ~junit_test_report_writer() override = default;

    void start_report() override;

    void end_report() override;

    void write(const test_summary& summary) override;

private:
    string _path;
    xml_writer _writer;
    ofstream _os;

    void write(
        const test_summary& summary,
        const test_result& result);
};

std::shared_ptr<test_report_writer> testfx::create_junit_report_writer(const std::string& path)
{
    return std::make_shared<junit_test_report_writer>(path);
}

junit_test_report_writer::junit_test_report_writer(const string& path)
    : _path(path), _os(path), _writer(_os)
{
}

void junit_test_report_writer::start_report()
{
    _writer.write_start_element("testsuites");
}

void junit_test_report_writer::end_report()
{
    _writer.write_full_end_element(); // </testsuites>
}

void junit_test_report_writer::write(const test_summary& summary)
{
    _writer.write_start_element("testsuite");
    _writer.write_attribute("name", summary.class_name());
    _writer.write_attribute("tests", summary.failed_tests() + summary.passed_tests());
    _writer.write_attribute("failures", summary.failed_tests());
    _writer.write_attribute("errors", "0");
    _writer.write_attribute("time", summary.total_duration().count());

    for (const auto& test_case : summary.results())
    {
        write(summary, test_case);
    }

    _writer.write_full_end_element(); // </testsuite>
}

void junit_test_report_writer::write(
    const test_summary& summary,
    const test_result& result)
{
    _writer.write_start_element("testcase");
    _writer.write_attribute("name", result.name());
    _writer.write_attribute("classname", summary.class_name());
    _writer.write_attribute("time", result.duration().count());
    string status_str = result.passed() ? "passed" : "failed";
    _writer.write_attribute("status", status_str);

    if (!result.passed())
    {
        _writer.write_start_element("failure");
        _writer.write_attribute("message", result.message());
        _writer.write_full_end_element(); // </failure>
    }

    _writer.write_full_end_element(); // </testcase>
}