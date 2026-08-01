/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 * Licensed under the MIT License. See LICENSE file in the project root for full license information.
 * @file enum_member_parse_node.cpp
 * @brief Implementation file for the enum_member_parse_node class.
 */
#include <parse_node.hpp>

using namespace std;
using namespace opendraft::lang;

enum_member_parse_node::enum_member_parse_node(
    const std::string& name,
    long value,
    bool has_value,
    const std::shared_ptr<token>& start,
    const std::list<std::shared_ptr<comment_token>>& preceding_comments)
    : program_element_parse_node(start, preceding_comments), _name(name), _value(value), _has_value(has_value)
{
}

parse_node_type enum_member_parse_node::type() const
{
    return parse_node_type::PARSE_NODE_ENUM_MEMBER;
}