/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 * Licensed under the MIT License. See LICENSE file in the project root for full license information.
 * @file program_element_parse_node.cpp
 * @brief Implementation file for the program_element_parse_node class.
 */
#include <parse_node.hpp>

using namespace std;
using namespace opendraft::lang;

program_element_parse_node::program_element_parse_node(
    const shared_ptr<token>& start,
    const list<shared_ptr<comment_token>>& preceding_comments)
    : parse_node(start, preceding_comments)
{
}