// <copyright file="KeywordToken.cs" company="Jon Rowlett">
// Copyright (c) Jon Rowlett. All rights reserved.
// </copyright>

namespace OpenDraft.Lang;

/// <summary>
/// Represents a keyword token in the language.
/// </summary>
public class KeywordToken : Token
{
    /// <summary>
    /// Initializes a new instance of the <see cref="KeywordToken"/> class.
    /// </summary>
    /// <param name="source">The source reference for this token.</param>
    /// <param name="value">The value of the keyword.</param>
    /// <exception cref="ArgumentNullException">Thrown if <paramref name="source"/> is null.</exception>
    /// <exception cref="ArgumentOutOfRangeException">Thrown if <paramref name="value"/> is <see cref="Keyword.None"/>.</exception>
    public KeywordToken(SourceReference source, Keyword value)
        : base(source)
    {
        this.Value = value != Keyword.None ?
            value :
            throw new ArgumentOutOfRangeException(nameof(value), "Value cannot be None.");
    }

    /// <summary>
    /// Gets the value of the keyword.
    /// </summary>
    public Keyword Value { get; }

    /// <inheritdoc/>
    public override string ToString()
    {
        return KeywordUtility.GetText(this.Value);
    }
}