/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 * Licensed under the MIT License. See LICENSE file in the project root for full license information.
 * @file string_literal_expression_parse_node.cpp
 * @brief Implementation file for the string_literal_expression_parse_node class.
 */
#include <parse_node.hpp>

using namespace std;
using namespace opendraft::lang;

string_literal_expression_parse_node::string_literal_expression_parse_node(
    const string& value,
    const shared_ptr<token>& start,
    const list<shared_ptr<comment_token>>& preceding_comments)
    : expression_parse_node(start, preceding_comments), _value(value)
{
}

parse_node_type string_literal_expression_parse_node::type() const
{
    return PARSE_NODE_STRING_LITERAL_EXPRESSION;
}