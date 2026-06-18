// <copyright file="StringLiteralToken.cs" company="Jon Rowlett">
// Copyright (c) Jon Rowlett. All rights reserved.
// </copyright>

namespace OpenDraft.Lang;

/// <summary>
/// Represents a string literal token in the language.
/// </summary>
public class StringLiteralToken : Token
{
    /// <summary>
    /// Initializes a new instance of the <see cref="StringLiteralToken"/> class.
    /// </summary>
    /// <param name="source">The source reference for this token.</param>
    /// <param name="value">The value of the string literal.</param>
    /// <exception cref="ArgumentNullException">Thrown if <paramref name="source"/> or <paramref name="value"/> is null.</exception>
    public StringLiteralToken(SourceReference source, string value)
        : base(source)
    {
        this.Value = value ?? throw new ArgumentNullException(nameof(value));
    }

    /// <summary>
    /// Gets the value of the string literal.
    /// </summary>
    public string Value { get; }
}