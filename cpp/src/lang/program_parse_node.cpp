/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 * Licensed under the MIT License. See LICENSE file in the project root for full license information.
 * @file program_parse_node.cpp
 * @brief Implementation file for the program_parse_node class.
 */
#include <parse_node.hpp>

using namespace std;
using namespace opendraft::lang;

program_parse_node::program_parse_node(
    const std::list<std::shared_ptr<import_parse_node>>& imports,
    const std::list<std::shared_ptr<program_element_parse_node>>& program_elements,
    const std::shared_ptr<token>& start,
    const std::list<std::shared_ptr<comment_token>>& preceding_comments)
    : parse_node(start, preceding_comments),
      _imports(imports),
      _program_elements(program_elements)
{
}

parse_node_type program_parse_node::type() const
{
    return parse_node_type::PARSE_NODE_PROGRAM;
}