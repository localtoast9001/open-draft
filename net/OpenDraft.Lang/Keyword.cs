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
    /// Represents the 'class' keyword.
    /// </summary>
    @Class,

    /// <summary>
    /// Represents the 'interface' keyword.
    /// </summary>
    @Interface,

    /// <summary>
    /// Represents the 'enum' keyword.
    /// </summary>
    @Enum,

    /// <summary>
    /// Represents the 'if' keyword.
    /// </summary>
    @If,

    /// <summary>
    /// Represents the 'for' keyword.
    /// </summary>
    @For,
}