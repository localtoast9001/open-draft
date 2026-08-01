/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 * Licensed under the MIT License. See LICENSE file in the project root for full license information.
 * @file function_declaration_parse_node.cpp
 * @brief Implementation file for the function_declaration_parse_node class.
 */
#include <parse_node.hpp>

using namespace std;
using namespace opendraft::lang;

function_declaration_parse_node::function_declaration_parse_node(
    const std::string& name,
    const std::list<std::shared_ptr<parameter_declaration_parse_node>>& parameters,
    const std::shared_ptr<token>& start,
    const std::list<std::shared_ptr<comment_token>>& preceding_comments)
    : interface_member_parse_node(start, preceding_comments), _name(name), _parameters(parameters)
{
}

parse_node_type function_declaration_parse_node::type() const
{
    return parse_node_type::PARSE_NODE_FUNCTION_DECLARATION;
}