// <copyright file="Keyword.cs" company="Jon Rowlett">
// Copyright (c) Jon Rowlett. All rights reserved.
// </copyright>

namespace OpenDraft.Lang;

/// <summary>
/// Represents a keyword in the language.
/// </summary>
public enum Keyword
{
    /// <summary>
    /// Represents no keyword.
    /// </summary>
    None = 0,

    /// <summary>
    /// Represents the 'break' keyword.
    /// </summary>
    Break,

    /// <summary>
    /// Represents the 'class' keyword.
    /// </summary>
    @Class,

    /// <summary>
    /// Represents the 'continue' keyword.
    /// </summary>
    Continue,

    /// <summary>
    /// Represents the 'debug' keyword.
    /// </summary>
    Debug,

    /// <summary>
    /// Represents the 'else' keyword.
    /// </summary>
    Else,

    /// <summary>
    /// Represents the 'enum' keyword.
    /// </summary>
    @Enum,

    /// <summary>
    /// Represents the 'error' keyword.
    /// </summary>
    Error,

    /// <summary>
    /// Represents the 'false' keyword.
    /// </summary>
    False,

    /// <summary>
    /// Represents the 'for' keyword.
    /// </summary>
    For,

    /// <summary>
    /// Represents the 'function' keyword.
    /// </summary>
    Function,

    /// <summary>
    /// Represents the 'if' keyword.
    /// </summary>
    If,

    /// <summary>
    /// Represents the 'import' keyword.
    /// </summary>
    Import,

    /// <summary>
    /// Represents the 'in' keyword.
    /// </summary>
    In,

    /// <summary>
    /// Represents the 'info' keyword.
    /// </summary>
    Info,

    /// <summary>
    /// Represents the 'interface' keyword.
    /// </summary>
    @Interface,

    /// <summary>
    /// Represents the 'namespace' keyword.
    /// </summary>
    Namespace,

    /// <summary>
    /// Represents the 'null' keyword.
    /// </summary>
    Null,

    /// <summary>
    /// Represents the 'return' keyword.
    /// </summary>
    Return,

    /// <summary>
    /// Represents the 'static' keyword.
    /// </summary>
    Static,

    /// <summary>
    /// Represents the 'template' keyword.
    /// </summary>
    Template,

    /// <summary>
    /// Represents the 'throw' keyword.
    /// </summary>
    Throw,

    /// <summary>
    /// Represents the 'true' keyword.
    /// </summary>
    True,

    /// <summary>
    /// Represents the 'verbose' keyword.
    /// </summary>
    Verbose,

    /// <summary>
    /// Represents the 'warn' keyword.
    /// </summary>
    Warn,
}