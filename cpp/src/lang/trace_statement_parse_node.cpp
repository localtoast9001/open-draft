/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 * Licensed under the MIT License. See LICENSE file in the project root for full license information.
 * @file trace_statement_parse_node.cpp
 * @brief Implementation file for the trace_statement_parse_node class.
 */
#include <parse_node.hpp>

using namespace std;
using namespace opendraft::lang;

trace_statement_parse_node::trace_statement_parse_node(
    trace_statement_severity severity,
    const std::shared_ptr<expression_parse_node>& expression,
    const std::shared_ptr<token>& start,
    const std::list<std::shared_ptr<comment_token>>& preceding_comments)
    : statement_parse_node(start, preceding_comments), _severity(severity), _expression(expression)
{
}

parse_node_type trace_statement_parse_node::type() const
{
    return PARSE_NODE_TRACE_STATEMENT;
}