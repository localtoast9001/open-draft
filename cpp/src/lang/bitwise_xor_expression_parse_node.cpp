/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 * Licensed under the MIT License. See LICENSE file in the project root for full license information.
 * @file bitwise_xor_expression_parse_node.cpp
 * @brief Implementation file for the bitwise_xor_expression_parse_node class.
 */
#include <parse_node.hpp>

using namespace std;
using namespace opendraft::lang;

bitwise_xor_expression_parse_node::bitwise_xor_expression_parse_node(
    const shared_ptr<expression_parse_node>& left,
    const shared_ptr<expression_parse_node>& right,
    const shared_ptr<token>& start,
    const list<shared_ptr<comment_token>>& preceding_comments)
    : expression_parse_node(start, preceding_comments),
      _left(left),
      _right(right)
{
}

parse_node_type bitwise_xor_expression_parse_node::type() const
{
    return parse_node_type::PARSE_NODE_BITWISE_XOR_EXPRESSION;
}