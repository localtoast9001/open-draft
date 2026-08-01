/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 * Licensed under the MIT License. See LICENSE file in the project root for full license information.
 * @file interface_parse_node.cpp
 * @brief Implementation file for the interface_parse_node class.
 */
#include <parse_node.hpp>

using namespace std;
using namespace opendraft::lang;

interface_parse_node::interface_parse_node(
    const std::string& name,
    const std::list<std::shared_ptr<interface_member_parse_node>>& members,
    const std::shared_ptr<token>& start,
    const std::list<std::shared_ptr<comment_token>>& preceding_comments)
    : program_element_parse_node(start, preceding_comments), _name(name), _members(members)
{
}

parse_node_type interface_parse_node::type() const
{
    return PARSE_NODE_INTERFACE;
}