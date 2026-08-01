/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 * Licensed under the MIT License. See LICENSE file in the project root for full license information.
 * @file conditional_expression_parse_node.cpp
 * @brief Implementation file for the conditional_expression_parse_node class.
 */
#include <parse_node.hpp>

using namespace std;
using namespace opendraft::lang;

conditional_expression_parse_node::conditional_expression_parse_node(
    const std::shared_ptr<expression_parse_node>& condition,
    const std::shared_ptr<expression_parse_node>& true_expression,
    const std::shared_ptr<expression_parse_node>& false_expression,
    const std::shared_ptr<token>& start,
    const std::list<std::shared_ptr<comment_token>>& preceding_comments)
    : expression_parse_node(start, preceding_comments),
      _condition(condition),
      _true_expression(true_expression),
      _false_expression(false_expression)
{
}

parse_node_type conditional_expression_parse_node::type() const
{
    return parse_node_type::PARSE_NODE_CONDITIONAL_EXPRESSION;
}