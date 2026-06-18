// <copyright file="CommentToken.cs" company="Jon Rowlett">
// Copyright (c) Jon Rowlett. All rights reserved.
// </copyright>

namespace OpenDraft.Lang;

/// <summary>
/// A comment token that appears in the source code.
/// </summary>
/// <remarks>
/// Comments are ignored but preserved in the token stream for preservation in compiler output and for use in tools that may want to analyze comments (e.g. documentation generators).
/// </remarks>
public class CommentToken : Token
{
    /// <summary>
    /// Initializes a new instance of the <see cref="CommentToken"/> class.
    /// </summary>
    /// <param name="source">The source reference for the token.</param>
    /// <param name="text">The text of the comment.</param>
    /// <param name="isBlock">Indicates whether the comment is a block comment.</param>
    /// <exception cref="ArgumentNullException">Thrown if <paramref name="text"/> is null.</exception>
    public CommentToken(
        SourceReference source,
        string text,
        bool isBlock)
        : base(source)
    {
        this.Text = text ?? throw new ArgumentNullException(nameof(text));
        this.IsBlock = isBlock;
    }

    /// <summary>
    /// Gets the text of the comment, excluding comment delimiters (e.g. // or /* */).
    /// </summary>
    public string Text { get; }

    /// <summary>
    /// Gets a value indicating whether this comment is a block comment (e.g. /* */) or a line comment (e.g. //).
    /// </summary>
    public bool IsBlock { get; }
}