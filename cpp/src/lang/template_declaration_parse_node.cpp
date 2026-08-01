/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 * Licensed under the MIT License. See LICENSE file in the project root for full license information.
 * @file template_declaration_parse_node.cpp
 * @brief Implementation file for the template_declaration_parse_node class.
 */
#include <parse_node.hpp>

using namespace std;
using namespace opendraft::lang;

template_declaration_parse_node::template_declaration_parse_node(
    const std::string& name,
    const std::list<std::shared_ptr<parameter_declaration_parse_node>>& parameters,
    const std::shared_ptr<token>& start,
    const std::list<std::shared_ptr<comment_token>>& preceding_comments)
    : interface_member_parse_node(start, preceding_comments), _name(name), _parameters(parameters)
{
}

parse_node_type template_declaration_parse_node::type() const
{
    return PARSE_NODE_TEMPLATE_DECLARATION;
}