/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 * Licensed under the MIT License. See LICENSE file in the project root for full license information.
 * @file add_expression_parse_node.cpp
 * @brief Implementation file for the add_expression_parse_node class.
 */

#include <parse_node.hpp>

using namespace std;
using namespace opendraft::lang;

add_expression_parse_node::add_expression_parse_node(
    const shared_ptr<expression_parse_node>& left,
    const shared_ptr<expression_parse_node>& right,
    bool is_subtraction,
    const shared_ptr<token>& start,
    const list<shared_ptr<comment_token>>& preceding_comments)
    : expression_parse_node(start, preceding_comments),
      _left(left),
      _right(right),
      _is_subtraction(is_subtraction)
{
}

parse_node_type add_expression_parse_node::type() const
{
    return parse_node_type::PARSE_NODE_ADD_EXPRESSION;
}

