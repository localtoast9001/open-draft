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

/**
 * @brief Determines if the parse node is an expression.
 * @return true if the parse node is an expression; otherwise, false.
 */
bool parse_node::is_expression() const
{
    return false;
}

/**
 * @brief Determines if the parse node is a statement.
 * @return true if the parse node is a statement; otherwise, false.
 */
bool parse_node::is_statement() const
{
    return false;
}

/**
 * @brief Determines if the parse node is a program element.
 * @return true if the parse node is a program element; otherwise, false.
 */
bool parse_node::is_program_element() const
{
    return false;
}

/**
 * @brief Determines if the parse node is an interface member.
 * @return true if the parse node is an interface member; otherwise, false.
 */
bool parse_node::is_interface_member() const
{
    return false;
}

/**
 * @brief Determines if the parse node is a reference expression.
 * @return true if the parse node is a reference expression; otherwise, false.
 */
bool parse_node::is_reference_expression() const
{
    return false;
}
