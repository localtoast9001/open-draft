// <copyright file="SymbolToken.cs" company="Jon Rowlett">
// Copyright (c) Jon Rowlett. All rights reserved.
// </copyright>

namespace OpenDraft.Lang;

/// <summary>
/// Represents a symbol token in the language.
/// </summary>
public class SymbolToken : Token
{
    /// <summary>
    /// Initializes a new instance of the <see cref="SymbolToken"/> class.
    /// </summary>
    /// <param name="source">The source reference for this token.</param>
    /// <param name="value">The value of the symbol.</param>
    /// <exception cref="ArgumentNullException">Thrown if <paramref name="source"/> is null.</exception>
    public SymbolToken(SourceReference source, Symbol value)
        : base(source)
    {
        this.Value = value;
    }

    /// <summary>
    /// Gets the value of the symbol.
    /// </summary>
    public Symbol Value { get; }
}