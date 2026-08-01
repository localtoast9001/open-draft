/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 * Licensed under the MIT License. See LICENSE file in the project root for full license information.
 * @file unary_expression_parse_node.cpp
 * @brief Implementation file for the unary_expression_parse_node class.
 */
#include <parse_node.hpp>

using namespace std;
using namespace opendraft::lang;

unary_expression_parse_node::unary_expression_parse_node(
    unary_operator op,
    const std::shared_ptr<expression_parse_node>& operand,
    const std::shared_ptr<token>& start,
    const std::list<std::shared_ptr<comment_token>>& preceding_comments)
    : expression_parse_node(start, preceding_comments), _op(op), _operand(operand)
{
}

parse_node_type unary_expression_parse_node::type() const
{
    return PARSE_NODE_UNARY_EXPRESSION;
}