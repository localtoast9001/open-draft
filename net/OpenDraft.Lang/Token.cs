// <copyright file="Token.cs" company="Jon Rowlett">
// Copyright (c) Jon Rowlett. All rights reserved.
// </copyright>

namespace OpenDraft.Lang;

/// <summary>
/// Base class for all tokens in the language.
/// </summary>
public abstract class Token
{
    /// <summary>
    /// Initializes a new instance of the <see cref="Token"/> class.
    /// </summary>
    /// <param name="source">The source reference for this token.</param>
    /// <exception cref="ArgumentNullException">Thrown if <paramref name="source"/> is null.</exception>
    protected Token(SourceReference source)
    {
        this.Source = source ?? throw new ArgumentNullException(nameof(source));
    }

    /// <summary>
    /// Gets the source reference for this token.
    /// </summary>
    public SourceReference Source { get; }
}