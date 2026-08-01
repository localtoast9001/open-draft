/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 * Licensed under the MIT License. See LICENSE file in the project root for full license information.
 * @file for_condition_parse_node.cpp
 * @brief Implementation file for the for_condition_parse_node class.
 */
#include <parse_node.hpp>

using namespace std;
using namespace opendraft::lang;

for_condition_parse_node::for_condition_parse_node(
    const std::list<std::string>& variable_names,
    const std::shared_ptr<expression_parse_node>& expression,
    const std::shared_ptr<type_reference_parse_node>& type_reference,
    const std::shared_ptr<token>& start,
    const std::list<std::shared_ptr<comment_token>>& preceding_comments)
    : parse_node(start, preceding_comments), _variable_names(variable_names), _expression(expression), _type_reference(type_reference)
{
}

parse_node_type for_condition_parse_node::type() const
{
    return parse_node_type::PARSE_NODE_FOR_CONDITION;
}