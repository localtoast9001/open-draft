/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 * Licensed under the MIT License. See LICENSE file in the project root for full license information.
 * @file expression_parse_node.cpp
 * @brief Implementation file for the expression_parse_node class.
 */
#include <parse_node.hpp>

using namespace std;
using namespace opendraft::lang;

expression_parse_node::expression_parse_node(
    const shared_ptr<token>& start,
    const list<shared_ptr<comment_token>>& preceding_comments)
    : parse_node(start, preceding_comments)
{
}