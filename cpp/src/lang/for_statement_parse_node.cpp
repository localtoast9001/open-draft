/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 * Licensed under the MIT License. See LICENSE file in the project root for full license information.
 * @file for_statement_parse_node.cpp
 * @brief Implementation file for the for_statement_parse_node class.
 */
#include <parse_node.hpp>

using namespace std;
using namespace opendraft::lang;

for_statement_parse_node::for_statement_parse_node(
    const std::list<std::shared_ptr<for_condition_parse_node>>& condition,
    const std::shared_ptr<statement_parse_node>& body,
    const std::shared_ptr<token>& start,
    const std::list<std::shared_ptr<comment_token>>& preceding_comments)
    : statement_parse_node(start, preceding_comments), _condition(condition), _body(body)
{
}

parse_node_type for_statement_parse_node::type() const
{
    return parse_node_type::PARSE_NODE_FOR_STATEMENT;
}