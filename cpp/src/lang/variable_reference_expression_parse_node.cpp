/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 * Licensed under the MIT License. See LICENSE file in the project root for full license information.
 * @file variable_reference_expression_parse_node.cpp
 * @brief Implementation file for the variable_reference_expression_parse_node class.
 */
#include <parse_node.hpp>

using namespace std;
using namespace opendraft::lang;

variable_reference_expression_parse_node::variable_reference_expression_parse_node(
    const std::string& name,
    const std::shared_ptr<token>& start,
    const std::list<std::shared_ptr<comment_token>>& preceding_comments)
    : reference_expression_parse_node(start, preceding_comments), _name(name)
{
}

parse_node_type variable_reference_expression_parse_node::type() const
{
    return PARSE_NODE_VARIABLE_REFERENCE;
}

shared_ptr<type_reference_parse_node> variable_reference_expression_parse_node::to_type_reference() const
{
    list<string> names;
    names.push_back(_name);
    return make_shared<type_reference_parse_node>(names, start(), preceding_comments());
}