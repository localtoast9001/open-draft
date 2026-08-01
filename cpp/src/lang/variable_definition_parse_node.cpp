/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 * Licensed under the MIT License. See LICENSE file in the project root for full license information.
 * @file variable_definition_parse_node.cpp
 * @brief Implementation file for the variable_definition_parse_node class.
 */
#include <parse_node.hpp>

using namespace std;
using namespace opendraft::lang;

variable_definition_parse_node::variable_definition_parse_node(
    const std::string& name,
    const std::shared_ptr<type_reference_parse_node>& type_reference,
    const std::shared_ptr<expression_parse_node>& value,
    const std::shared_ptr<token>& start,
    const std::list<std::shared_ptr<comment_token>>& preceding_comments)
    : statement_parse_node(start, preceding_comments), _name(name), _type_reference(type_reference), _value(value)
{
}

parse_node_type variable_definition_parse_node::type() const
{
    return PARSE_NODE_VARIABLE_DEFINITION;
}