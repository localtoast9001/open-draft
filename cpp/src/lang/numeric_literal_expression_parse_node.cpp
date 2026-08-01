/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 * Licensed under the MIT License. See LICENSE file in the project root for full license information.
 * @file numeric_literal_expression_parse_node.cpp
 * @brief Implementation file for the numeric_literal_expression_parse_node class.
 */
#include <parse_node.hpp>

using namespace std;
using namespace opendraft::lang;

numeric_literal_expression_parse_node::numeric_literal_expression_parse_node(
    double float_value,
    long integer_value,
    bool is_integer,
    const shared_ptr<token>& start,
    const list<shared_ptr<comment_token>>& preceding_comments)
    : expression_parse_node(start, preceding_comments),
      _float_value(float_value),
      _integer_value(integer_value),
      _is_integer(is_integer)
{
}

parse_node_type numeric_literal_expression_parse_node::type() const
{
    return PARSE_NODE_NUMERIC_LITERAL_EXPRESSION;
}