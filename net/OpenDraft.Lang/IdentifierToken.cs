// <copyright file="IdentifierToken.cs" company="Jon Rowlett">
// Copyright (c) Jon Rowlett. All rights reserved.
// </copyright>

namespace OpenDraft.Lang;

/// <summary>
/// Represents an identifier token in the language.
/// </summary>
public class IdentifierToken : Token
{
    /// <summary>
    /// Initializes a new instance of the <see cref="IdentifierToken"/> class.
    /// </summary>
    /// <param name="source">The source reference for this token.</param>
    /// <param name="value">The value of the identifier.</param>
    /// <exception cref="ArgumentNullException">Thrown if <paramref name="source"/> or <paramref name="value"/> is null.</exception>
    public IdentifierToken(SourceReference source, string value)
        : base(source)
    {
        this.Value = value ?? throw new ArgumentNullException(nameof(value));
    }

    /// <summary>
    /// Gets the value of the identifier.
    /// </summary>
    public string Value { get; }
}