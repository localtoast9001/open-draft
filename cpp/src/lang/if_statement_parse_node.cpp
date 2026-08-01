/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 * Licensed under the MIT License. See LICENSE file in the project root for full license information.
 * @file if_statement_parse_node.cpp
 * @brief Implementation file for the if_statement_parse_node class.
 */
#include <parse_node.hpp>

using namespace std;
using namespace opendraft::lang;

if_statement_parse_node::if_statement_parse_node(
    const std::shared_ptr<expression_parse_node>& condition,
    const std::shared_ptr<statement_parse_node>& then_statement,
    const std::shared_ptr<statement_parse_node>& else_statement,
    const std::shared_ptr<token>& start,
    const std::list<std::shared_ptr<comment_token>>& preceding_comments)
    : statement_parse_node(start, preceding_comments), _condition(condition), _then_statement(then_statement), _else_statement(else_statement)
{
}

parse_node_type if_statement_parse_node::type() const
{
    return parse_node_type::PARSE_NODE_IF_STATEMENT;
}