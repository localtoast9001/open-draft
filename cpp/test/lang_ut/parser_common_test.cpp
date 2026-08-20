/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 * Licensed under the MIT license. See LICENSE file in the project root for full license information.
 * @file parser_common_test.cpp
 * @brief Runs the shared set of test cases for the parser.
 */
#include <testfx.hpp>
#include <parser.hpp>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <tools/parse_tree_xml_exporter.hpp>

using namespace testfx;
using namespace std;
using namespace std::filesystem;
using namespace opendraft::lang;
using namespace opendraft::lang::tools;

class parser_common_test : public test_class
{
public:
    static parser_common_test instance;

    parser_common_test()
        : test_class("parser_common_test")
    {
    }

    void init(test_context& context) override;

private:
    void run_test_case(
        const string& test_name,
        const path& input_file_path);

    parser_common_test(const parser_common_test&) = delete;
    parser_common_test& operator=(const parser_common_test&) = delete;
};

parser_common_test parser_common_test::instance;

void parser_common_test::init(test_context& context)
{
    // enumerate the *.odl files in the testcases/parser directory and add a test for each one
    const std::string testcases_dir = context.get_test_program_dir_path() + "/testcases/parser";
    for (const auto& entry : std::filesystem::directory_iterator(testcases_dir))
    {
        if (entry.is_regular_file() && entry.path().extension() == ".odl")
        {
            const std::string test_name = entry.path().stem().string();
            auto input_file_path = entry.path();
            add(test_name, [&, test_name, input_file_path](test_class& cls)
            {
                run_test_case(test_name, input_file_path);
            });
        }
    }
}

void parser_common_test::run_test_case(
    const string& test_name,
    const path& input_file_path)
{
    list<message> log;

    // Read the input file
    ifstream input_file(input_file_path);
    source_reference start_source(input_file_path.string(), 1, 1);
    auto log_callback = [&](const message& msg) { log.push_back(msg); };
    token_reader reader( 
        input_file,
        start_source,
        log_callback);

    // Create a parser instance and parse the input content
    parser p(log_callback, reader);
    auto program_node = p.parse();

    // dump messages to stderr.
    for (const auto& msg : log)
    {
        cerr << msg << endl;
    }

    assert_not_null(program_node);
    assert_equal((size_t)0, log.size());

    // load the expected output file
    path expected_output_file_path = input_file_path;
    expected_output_file_path.replace_extension(".xml");
    ifstream expected_output_file(expected_output_file_path);
    std::ostringstream expected_output_stream;
    expected_output_stream << expected_output_file.rdbuf();
    const std::string expected_output = expected_output_stream.str();
    expected_output_file.close();

    // dump the parse tree to xml.
    std::ostringstream actual_output_stream;
    parse_tree_xml_exporter exporter(actual_output_stream);

    // add the utf-8 BOM to the output stream to simplify the comparison.
    actual_output_stream << "\xEF\xBB\xBF";
    exporter.export_program(*program_node);
    const std::string actual_output = actual_output_stream.str();

    assert_equal(expected_output, actual_output);
}
