/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 * Licensed under the MIT License. See LICENSE.md in the project root for license information.
 */
package io.github.localtoast9001.opendraft.lang;

/**
 * Symbols used in the OpenDraft language.
 */
public enum Symbol {
    UNDEFINED,
    LEFT_PAREN,
    RIGHT_PAREN,
    LEFT_BRACE,
    RIGHT_BRACE,
    LEFT_BRACKET,
    RIGHT_BRACKET,
    COMMA,
    DOT,
    SEMICOLON,
    PLUS,
    MINUS,
    STAR,
    SLASH,
    EQUAL,
    LESS,
    GREATER,
    BANG,
    AMPERSAND,
    PIPE;

    static Symbol fromString(String str) {
        if (str == null) {
            return UNDEFINED;
        }

        switch (str) {
            case "(":
                return LEFT_PAREN;
            case ")":
                return RIGHT_PAREN;
            case "{":
                return LEFT_BRACE;
            case "}":
                return RIGHT_BRACE;
            case "[":
                return LEFT_BRACKET;
            case "]":
                return RIGHT_BRACKET;
            case ",":
                return COMMA;
            case ".":
                return DOT;
            case ";":
                return SEMICOLON;
            case "+":
                return PLUS;
            case "-":
                return MINUS;
            case "*":
                return STAR;
            case "/":
                return SLASH;
            case "=":
                return EQUAL;
            case "<":
                return LESS;
            case ">":
                return GREATER;
            case "!":
                return BANG;
            case "&":
                return AMPERSAND;
            case "|":
                return PIPE;
            default:
                return UNDEFINED;
        }
    }
}
