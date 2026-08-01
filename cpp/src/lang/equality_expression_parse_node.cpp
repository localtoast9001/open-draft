/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 * Licensed under the MIT License. See LICENSE file in the project root for full license information.
 * @file equality_expression_parse_node.cpp
 * @brief Implementation file for the equality_expression_parse_node class.
 */
#include <parse_node.hpp>

using namespace std;
using namespace opendraft::lang;

equality_expression_parse_node::equality_expression_parse_node(
    const std::shared_ptr<expression_parse_node>& left,
    const std::shared_ptr<expression_parse_node>& right,
    bool is_inequality,
    const std::shared_ptr<token>& start,
    const std::list<std::shared_ptr<comment_token>>& preceding_comments)
    : expression_parse_node(start, preceding_comments), _left(left), _right(right), _is_inequality(is_inequality)
{
}

parse_node_type equality_expression_parse_node::type() const
{
    return parse_node_type::PARSE_NODE_EQUALITY_EXPRESSION;
}