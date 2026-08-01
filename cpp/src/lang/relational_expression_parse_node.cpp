/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 * Licensed under the MIT License. See LICENSE file in the project root for full license information.
 * @file relational_expression_parse_node.cpp
 * @brief Implementation file for the relational_expression_parse_node class.
 */
#include <parse_node.hpp>

using namespace std;
using namespace opendraft::lang;

relational_expression_parse_node::relational_expression_parse_node(
    const std::shared_ptr<expression_parse_node>& left,
    const std::shared_ptr<expression_parse_node>& right,
    relational_operator op,
    const std::shared_ptr<token>& start,
    const std::list<std::shared_ptr<comment_token>>& preceding_comments)
    : expression_parse_node(start, preceding_comments), _left(left), _right(right), _op(op)
{
}

parse_node_type relational_expression_parse_node::type() const
{
    return PARSE_NODE_RELATIONAL_EXPRESSION;
}