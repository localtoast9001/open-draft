/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 * Licensed under the MIT License. See LICENSE file in the project root for full license information.
 * @file call_expression_parse_node.cpp
 * @brief Implementation file for the call_expression_parse_node class.
 */
#include <parse_node.hpp>

using namespace std;
using namespace opendraft::lang;

call_expression_parse_node::call_expression_parse_node(
    const shared_ptr<reference_expression_parse_node>& target,
    const list<shared_ptr<argument_parse_node>>& arguments,
    const shared_ptr<token>& start,
    const list<shared_ptr<comment_token>>& preceding_comments)
    : reference_expression_parse_node(start, preceding_comments), _target(target), _arguments(arguments)
{
}

parse_node_type call_expression_parse_node::type() const
{
    return parse_node_type::PARSE_NODE_CALL_EXPRESSION;
}