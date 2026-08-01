/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 * Licensed under the MIT License. See LICENSE file in the project root for full license information.
 * @file member_reference_expression_parse_node.cpp
 * @brief Implementation file for the member_reference_expression_parse_node class.
 */
#include <parse_node.hpp>

using namespace std;
using namespace opendraft::lang;

member_reference_expression_parse_node::member_reference_expression_parse_node(
    const std::shared_ptr<reference_expression_parse_node>& target,
    const std::string& member_name,
    const std::shared_ptr<token>& start,
    const std::list<std::shared_ptr<comment_token>>& preceding_comments)
    : reference_expression_parse_node(start, preceding_comments), _target(target), _member_name(member_name)
{
}

parse_node_type member_reference_expression_parse_node::type() const
{
    return PARSE_NODE_MEMBER_REFERENCE_EXPRESSION;
}

shared_ptr<type_reference_parse_node> member_reference_expression_parse_node::to_type_reference() const
{
    auto target_as_type_ref = _target->to_type_reference();
    if (!target_as_type_ref)
    {
        return nullptr;
    }

    list<string> names = target_as_type_ref->names();
    names.push_back(_member_name);

    return make_shared<type_reference_parse_node>(
        names,
        start(),
        preceding_comments());
}