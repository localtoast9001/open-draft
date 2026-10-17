/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 * @file test_runner_options.cpp
 * @brief Implementation of the test_runner_options class.
 */
#include "testfx.hpp"

using namespace std;
using namespace testfx;

enum report_format
{
    REPORT_FORMAT_NONE = 0,
    REPORT_FORMAT_JUNIT,
};

/**
 * @brief Represents the command-line arguments for the test runner.
 */
class arguments
{
public:
    bool parse(int argc, const char* argv[]);

    inline const string& report_file() const { return _report_file; }
    constexpr ::report_format report_format() const { return _report_format; }
private:
    string _report_file;
    ::report_format _report_format;
};

test_runner_options::test_runner_options()
: _report_writer_factory(testfx::create_blank_report_writer)
{
}

bool test_runner_options::init(int argc, const char* argv[])
{
    arguments args;
    if (!args.parse(argc, argv))
    {
        return false;
    }

    // Set the report writer factory based on the parsed report format.
    switch (args.report_format())
    {
    case REPORT_FORMAT_NONE:
        _report_writer_factory = testfx::create_blank_report_writer;
        break;
    case REPORT_FORMAT_JUNIT:
        _report_writer_factory = [path = args.report_file()]() {
            return testfx::create_junit_report_writer(path);
        };
        break;
    default:
        return false;
    }

    return true;
}

bool arguments::parse(int argc, const char* argv[])
{
    // Simple argument parsing logic (for demonstration purposes)
    _report_format = REPORT_FORMAT_NONE;
    for (int i = 1; i < argc; ++i)
    {
        string arg = argv[i];
        if (arg == "--report-file" && i + 1 < argc)
        {
            _report_file = argv[++i];
            _report_format = REPORT_FORMAT_JUNIT;
        }
        else if (arg == "--report-format" && i + 1 < argc)
        {
            string format = argv[++i];
            if (format == "junit")
            {
                _report_format = REPORT_FORMAT_JUNIT;
            }
            else if (format == "none")
            {
                _report_format = REPORT_FORMAT_NONE;
            }
            else
            {
                return false; // Unknown format
            }
        }
    }
    
    return true;
}