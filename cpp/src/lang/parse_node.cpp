/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 * Licensed under the MIT License. See LICENSE file in the project root for full license information.
 * @file parse_node.cpp
 * @brief Implementation file for the parse_node class.
 */
#include <parse_node.hpp>

using namespace std;
using namespace opendraft::lang;

parse_node::parse_node(
    const shared_ptr<token>& start,
    const list<shared_ptr<comment_token>>& preceding_comments)
    : _start(start), _preceding_comments(preceding_comments)
{
}