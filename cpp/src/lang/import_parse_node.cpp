/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 * Licensed under the MIT License. See LICENSE file in the project root for full license information.
 * @file import_parse_node.cpp
 * @brief Implementation file for the import_parse_node class.
 */

#include <parse_node.hpp>

using namespace std;
using namespace opendraft::lang;

import_parse_node::import_parse_node(
    const std::string& module_name,
    const std::shared_ptr<token>& start,
    const std::list<std::shared_ptr<comment_token>>& preceding_comments)
    : parse_node(start, preceding_comments),
      _module_name(module_name)
{
}

parse_node_type import_parse_node::type() const
{
    return parse_node_type::PARSE_NODE_IMPORT;
}