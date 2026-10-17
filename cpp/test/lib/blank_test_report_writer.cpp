/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 * @file blank_test_report_writer.cpp
 * @brief Implementation of the blank_test_report_writer class.
 */
#include "testfx.hpp"

using namespace testfx;

class blank_test_report_writer : public test_report_writer
{
public:
    blank_test_report_writer() = default;
    ~blank_test_report_writer() override = default;

    void start_report() override
    {
        // Implementation for starting the blank report.
    }

    void end_report() override
    {
        // Implementation for ending the blank report.
    }

    void write(const test_summary& summary) override
    {
        // Implementation for writing the test summary to the blank report.
    }
};

std::shared_ptr<test_report_writer> testfx::create_blank_report_writer()
{
    return std::make_shared<blank_test_report_writer>();
}