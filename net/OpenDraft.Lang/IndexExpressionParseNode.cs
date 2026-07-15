// <copyright file="IndexExpressionParseNode.cs" company="Jon Rowlett">
// Copyright (c) Jon Rowlett. All rights reserved.
// </copyright>

namespace OpenDraft.Lang;

/// <summary>
/// Represents an index expression in the language.
/// </summary>
public class IndexExpressionParseNode : ReferenceExpressionParseNode
{
    /// <summary>
    /// Initializes a new instance of the <see cref="IndexExpressionParseNode"/> class.
    /// </summary>
    /// <param name="target">The target of the index expression.</param>
    /// <param name="index">The index expression.</param>
    /// <param name="start">The starting token of the index expression.</param>
    /// <param name="precedingComments">The comments preceding the index expression.</param>
    public IndexExpressionParseNode(
        ReferenceExpressionParseNode target,
        ExpressionParseNode index,
        Token start,
        IEnumerable<CommentToken> precedingComments)
        : base(start, precedingComments)
    {
        this.Target = target ?? throw new ArgumentNullException(nameof(target));
        this.Index = index ?? throw new ArgumentNullException(nameof(index));
    }

    /// <summary>
    /// Gets the target of the index expression.
    /// </summary>
    public ReferenceExpressionParseNode Target { get; }

    /// <summary>
    /// Gets the index expression.
    /// </summary>
    public ExpressionParseNode Index { get; }
}