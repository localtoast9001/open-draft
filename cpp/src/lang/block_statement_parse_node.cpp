/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 * Licensed under the MIT License. See LICENSE file in the project root for full license information.
 * @file block_statement_parse_node.cpp
 * @brief Implementation file for the block_statement_parse_node class.
 */
#include <parse_node.hpp>

using namespace std;
using namespace opendraft::lang;

block_statement_parse_node::block_statement_parse_node(
    const list<shared_ptr<statement_parse_node>>& statements,
    const shared_ptr<token>& start,
    const list<shared_ptr<comment_token>>& preceding_comments)
    : statement_parse_node(start, preceding_comments),
      _statements(statements)
{
}

parse_node_type block_statement_parse_node::type() const
{
    return parse_node_type::PARSE_NODE_BLOCK_STATEMENT;
}