/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 * Licensed under the MIT license. See LICENSE file in the project root for full license information.
 * @file main.cpp
 * @brief Main entry point for the odlang2xml tool.
 */
#include <iostream>
#include <tools/parse_tree_xml_exporter.hpp>
#include <parser.hpp>
#include <fstream>

using namespace std;
using namespace opendraft::lang;
using namespace opendraft::lang::tools;

void print_usage();
bool open_input_stream(const string& input_file, ifstream& input_stream);
bool open_output_stream(const string& output_file, ofstream& output_stream);
void log_callback(const message& m);

int main(int argc, const char* argv[])
{
    if (argc < 2 || argc > 3)
    {
        print_usage();
        return 1;
    }

    string input_file = argv[1];
    string output_file;
    if (argc == 3)
    {
        output_file = argv[2];
    }

    ifstream input_stream;
    if (!open_input_stream(input_file, input_stream))
    {
        return 1;
    }

    source_reference start_source(input_file, 1, 1);
    token_reader reader(
        input_stream,
        start_source,
        log_callback);
    parser p(log_callback, reader);
    auto root = p.parse();
    if (!root)
    {
        cerr << "Error: Failed to parse input file." << endl;
        return 1;
    }

    ofstream output_stream;
    if (!open_output_stream(output_file, output_stream))
    {
        return 1;
    }

    parse_tree_xml_exporter exporter(output_stream);
    exporter.export_program(*root);

    return 0;
}

bool open_input_stream(const string& input_file, ifstream& input_stream)
{
    if (input_file == "--")
    {
        // Read from standard input
        input_stream.basic_ios<char>::rdbuf(cin.rdbuf());
    }
    else
    {
        // Open the specified input file
        input_stream.open(input_file);
        if (!input_stream.is_open())
        {
            cerr << "Error: Could not open input file: " << input_file << endl;
            return false;
        }
    }

    return true;
}

bool open_output_stream(const string& output_file, ofstream& output_stream)
{
    if (output_file.empty())
    {
        // Write to standard output
        output_stream.basic_ios<char>::rdbuf(cout.rdbuf());
    }
    else
    {
        // Open the specified output file
        output_stream.open(output_file);
        if (!output_stream.is_open())
        {
            cerr << "Error: Could not open output file: " << output_file << endl;
            return false;
        }
    }

    return true;
}

void log_callback(const message& m)
{
    if (m.severity() == severity::SEVERITY_ERROR)
    {
        std::cerr << m.text() << endl;
    }
    else
    {
        cout << m.text() << endl;
    }
}

void print_usage()
{
    cout << "Usage: odlang2xml <input_file> [output_file]" << endl;
    cout << "Converts an OpenDraft language file to XML format." << endl;
    cout << "If the input file is '--', the program reads from standard input." << endl;
    cout << "If the output file is not specified, the program writes to standard output." << endl;
}