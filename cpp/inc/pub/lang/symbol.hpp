/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 * Licensed under the MIT license. See LICENSE file in the project root for full license information.
 * @file symbol.hpp
 * @brief Declares the symbol enum and related functions.
 */
#pragma once

#ifndef __OPENDRAFT_LANG_SYMBOL_HPP__
#define __OPENDRAFT_LANG_SYMBOL_HPP__

#include <ostream>

namespace opendraft::lang
{
    /**
     * @brief Represents the symbols in the OpenDraft language.
     */
    enum class symbol
    {
        SYMBOL_UNDEFINED = 0,
        SYMBOL_TILDE,               // ~
        SYMBOL_PERCENT,             // %
        SYMBOL_AMPERSAND,           // &
        SYMBOL_AND,                 // &&
        SYMBOL_STAR,                // *
        SYMBOL_LEFT_PAREN,          // (
        SYMBOL_RIGHT_PAREN,         // )
        SYMBOL_MINUS,               // -
        SYMBOL_PLUS,                // +
        SYMBOL_ASSIGN,              // =
        SYMBOL_EQUALS,              // ==
        SYMBOL_NOT_EQUALS,          // !=
        SYMBOL_LEFT_BRACKET,        // [
        SYMBOL_RIGHT_BRACKET,       // ]
        SYMBOL_LEFT_BRACE,          // {
        SYMBOL_RIGHT_BRACE,         // }
        SYMBOL_SLASH,               // /
        SYMBOL_PIPE,                // |
        SYMBOL_OR,                  // ||
        SYMBOL_COLON,               // :
        SYMBOL_SEMICOLON,           // ;
        SYMBOL_COMMA,               // ,
        SYMBOL_LESS_THAN,           // <
        SYMBOL_LESS_THAN_EQUALS,    // <=
        SYMBOL_GREATER_THAN,        // >
        SYMBOL_GREATER_THAN_EQUALS, // >=
        SYMBOL_LEFT_SHIFT,          // <<
        SYMBOL_RIGHT_SHIFT,         // >>
        SYMBOL_QUESTION,            // ?
        SYMBOL_DOUBLE_QUESTION,     // ??
        SYMBOL_DOT,                 // .
        SYMBOL_DOTDOT,              // ..
        SYMBOL_BANG,                // !
    };

    /**
     * @brief Converts a symbol enum value to its string representation.
     * @param value The symbol enum value to convert.
     * @return The string representation of the symbol.
     */
    const char* to_string(symbol value);

    std::ostream& operator<<(std::ostream& os, symbol value);
}

#endif /* __OPENDRAFT_LANG_SYMBOL_HPP__ */