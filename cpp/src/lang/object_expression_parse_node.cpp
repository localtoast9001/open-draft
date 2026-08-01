/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 * Licensed under the MIT License. See LICENSE file in the project root for full license information.
 * @file object_expression_parse_node.cpp
 * @brief Implementation file for the object_expression_parse_node class.
 */
#include <parse_node.hpp>

using namespace std;
using namespace opendraft::lang;

object_expression_parse_node::object_expression_parse_node(
    const std::list<std::shared_ptr<object_member_parse_node>>& members,
    const std::shared_ptr<token>& start,
    const std::list<std::shared_ptr<comment_token>>& preceding_comments)
    : expression_parse_node(start, preceding_comments), _members(members)
{
}

parse_node_type object_expression_parse_node::type() const
{
    return PARSE_NODE_OBJECT_EXPRESSION;
}