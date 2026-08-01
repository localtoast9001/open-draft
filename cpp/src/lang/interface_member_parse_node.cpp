/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 * Licensed under the MIT License. See LICENSE file in the project root for full license information.
 * @file interface_member_parse_node.cpp
 * @brief Implementation file for the interface_member_parse_node class.
 */
#include <parse_node.hpp>

using namespace std;
using namespace opendraft::lang;

interface_member_parse_node::interface_member_parse_node(
    const std::shared_ptr<token>& start,
    const std::list<std::shared_ptr<comment_token>>& preceding_comments)
    : parse_node(start, preceding_comments)
{
}