// <copyright file="ParseNode.cs" company="Jon Rowlett">
// Copyright (c) Jon Rowlett. All rights reserved.
// </copyright>

namespace OpenDraft.Lang;

/// <summary>
/// Represents a node in the parse tree. This is the base class for all parse nodes.
/// </summary>
public abstract class ParseNode
{
    /// <summary>
    /// Initializes a new instance of the <see cref="ParseNode"/> class.
    /// </summary>
    /// <param name="start">The token that starts this parse node.</param>
    /// <param name="precedingComments">The list of comments that precede this parse node.</param>
    /// <exception cref="ArgumentNullException">
    /// Thrown when <paramref name="start"/> or <paramref name="precedingComments"/> is <c>null</c>.
    /// </exception>
    protected ParseNode(
        Token start,
        IEnumerable<CommentToken> precedingComments)
    {
        this.Start = start ?? throw new ArgumentNullException(nameof(start));
        this.PrecedingComments = precedingComments?.ToList() ?? throw new ArgumentNullException(nameof(precedingComments));
    }

    /// <summary>
    /// Gets the token that starts this parse node. This is used for error reporting and other purposes.
    /// </summary>
    public Token Start { get; }

    /// <summary>
    /// Gets the list of comments that precede this parse node.
    /// </summary>
    public IReadOnlyList<CommentToken> PrecedingComments { get; }
}
