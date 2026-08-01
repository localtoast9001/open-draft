/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 * Licensed under the MIT License. See LICENSE file in the project root for full license information.
 * @file namespace_parse_node.cpp
 * @brief Implementation file for the namespace_parse_node class.
 */
#include <parse_node.hpp>

using namespace std;
using namespace opendraft::lang;

namespace_parse_node::namespace_parse_node(
    const std::string& name,
    const std::list<std::shared_ptr<program_element_parse_node>>& program_elements,
    const std::shared_ptr<token>& start,
    const std::list<std::shared_ptr<comment_token>>& preceding_comments)
    : program_element_parse_node(start, preceding_comments), _name(name), _program_elements(program_elements)
{
}

parse_node_type namespace_parse_node::type() const
{
    return PARSE_NODE_NAMESPACE;
}