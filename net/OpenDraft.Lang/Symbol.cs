// <copyright file="Symbol.cs" company="Jon Rowlett">
// Copyright (c) Jon Rowlett. All rights reserved.
// </copyright>

namespace OpenDraft.Lang;

/// <summary>
/// Represents a symbol in the language.
/// </summary>
public enum Symbol
{
    /// <summary>
    /// Represents no symbol.
    /// </summary>
    None = 0,

    /// <summary>
    /// Represents the '{' symbol.
    /// </summary>
    LeftBrace,

    /// <summary>
    /// Represents the '}' symbol.
    /// </summary>
    RightBrace,

    /// <summary>
    /// Represents the '(' symbol.
    /// </summary>
    LeftParen,

    /// <summary>
    /// Represents the ')' symbol.
    /// </summary>
    RightParen,

    /// <summary>
    /// Represents the '[' symbol.
    /// </summary>
    LeftBracket,

    /// <summary>
    /// Represents the ']' symbol.
    /// </summary>
    RightBracket,

    /// <summary>
    /// Represents the ';' symbol.
    /// </summary>
    Semicolon,

    /// <summary>
    /// Represents the ':' symbol.
    /// </summary>
    Colon,

    /// <summary>
    /// Represents the ',' symbol.
    /// </summary>
    Comma,

    /// <summary>
    /// Represents the '.' symbol.
    /// </summary>
    Dot,

    /// <summary>
    /// Represents the '+' symbol.
    /// </summary>
    Plus,

    /// <summary>
    /// Represents the '-' symbol.
    /// </summary>
    Minus,

    /// <summary>
    /// Represents the '*' symbol.
    /// </summary>
    Asterisk,

    /// <summary>
    /// Represents the '/' symbol.
    /// </summary>
    Slash,

    /// <summary>
    /// Represents the '%' symbol.
    /// </summary>
    Modulus,

    /// <summary>
    /// Represents the '..' symbol.
    /// </summary>
    Range,

    /// <summary>
    /// Represents the '=' symbol.
    /// </summary>
    Assignment,

    /// <summary>
    /// Represents the '==' symbol.
    /// </summary>
    Equals,

    /// <summary>
    /// Represents the '!=' symbol.
    /// </summary>
    NotEquals,

    /// <summary>
    /// Represents the '&lt;' symbol.
    /// </summary>
    LessThan,

    /// <summary>
    /// Represents the '&gt;' symbol.
    /// </summary>
    GreaterThan,

    /// <summary>
    /// Represents the '&lt;=' symbol.
    /// </summary>
    LessThanOrEqual,

    /// <summary>
    /// Represents the '&gt;=' symbol.
    /// </summary>
    GreaterThanOrEqual,

    /// <summary>
    /// Represents the '^' symbol.
    /// </summary>
    Caret,

    /// <summary>
    /// Represents the '~' symbol.
    /// </summary>
    Tilde,

    /// <summary>
    /// Represents the '?' symbol.
    /// </summary>
    Question,

    /// <summary>
    /// Represents the '|' symbol.
    /// </summary>
    Pipe,

    /// <summary>
    /// Represents the '||' symbol.
    /// </summary>
    DoublePipe,

    /// <summary>
    /// Represents the '&amp;' symbol.
    /// </summary>
    Ampersand,

    /// <summary>
    /// Represents the '&amp;&amp;' symbol.
    /// </summary>
    DoubleAmpersand,

    /// <summary>
    /// Represents the '!' symbol.
    /// </summary>
    Bang,

    /// <summary>
    /// Represents the '??' symbol.
    /// </summary>
    DoubleQuestion,

    /// <summary>
    /// Represents the '&lt;&lt;' symbol.
    /// </summary>
    DoubleLessThan,

    /// <summary>
    /// Represents the '&gt;&gt;' symbol.
    /// </summary>
    DoubleGreaterThan,
}