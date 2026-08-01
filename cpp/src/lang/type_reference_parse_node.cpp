/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 * Licensed under the MIT License. See LICENSE file in the project root for full license information.
 * @file type_reference_parse_node.cpp
 * @brief Implementation file for the type_reference_parse_node class.
 */
#include <parse_node.hpp>

using namespace std;
using namespace opendraft::lang;


type_reference_parse_node::type_reference_parse_node(
    const std::list<std::string>& names,
    const std::shared_ptr<token>& start,
    const std::list<std::shared_ptr<comment_token>>& preceding_comments)
    : parse_node(start, preceding_comments), _names(names)
{
}

parse_node_type type_reference_parse_node::type() const
{
    return PARSE_NODE_TYPE_REFERENCE;
}