// <copyright file="LiteralExpressionParseNode.cs" company="Jon Rowlett">
// Copyright (c) Jon Rowlett. All rights reserved.
// </copyright>

namespace OpenDraft.Lang;

/// <summary>
/// Represents a literal expression parse node.
/// </summary>
/// <typeparam name="T">The type of the literal value.</typeparam>
public class LiteralExpressionParseNode<T> : ExpressionParseNode
{
    /// <summary>
    /// Initializes a new instance of the <see cref="LiteralExpressionParseNode{T}"/> class.
    /// </summary>
    /// <param name="value">The value of the literal expression.</param>
    /// <param name="start">The starting token of the expression.</param>
    /// <param name="precedingComments">The comments preceding the expression.</param>
    public LiteralExpressionParseNode(
        T value,
        Token start,
        IEnumerable<CommentToken> precedingComments)
        : base(start, precedingComments)
    {
        this.Value = value;
    }

    /// <summary>
    /// Gets the value of the literal expression.
    /// </summary>
    public T Value { get; }
}