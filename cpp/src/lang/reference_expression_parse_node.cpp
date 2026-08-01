/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 * Licensed under the MIT License. See LICENSE file in the project root for full license information.
 * @file reference_expression_parse_node.cpp
 * @brief Implementation file for the reference_expression_parse_node class.
 */
#include <parse_node.hpp>

using namespace std;
using namespace opendraft::lang;

reference_expression_parse_node::reference_expression_parse_node(
    const shared_ptr<token>& start,
    const list<shared_ptr<comment_token>>& preceding_comments)
    : expression_parse_node(start, preceding_comments)
{
}

shared_ptr<type_reference_parse_node> reference_expression_parse_node::to_type_reference() const
{
    return nullptr;
}
