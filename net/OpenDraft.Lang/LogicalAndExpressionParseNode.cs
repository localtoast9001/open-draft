// <copyright file="LogicalAndExpressionParseNode.cs" company="Jon Rowlett">
// Copyright (c) Jon Rowlett. All rights reserved.
// </copyright>

namespace OpenDraft.Lang;

/// <summary>
/// Represents a logical AND expression parse node.
/// </summary>
public class LogicalAndExpressionParseNode : ExpressionParseNode
{
    /// <summary>
    /// Initializes a new instance of the <see cref="LogicalAndExpressionParseNode"/> class.
    /// </summary>
    /// <param name="left">The left operand of the logical AND expression.</param>
    /// <param name="right">The right operand of the logical AND expression.</param>
    /// <param name="start">The starting token of the logical AND expression.</param>
    /// <param name="preceedingComments">The comments preceding the logical AND expression.</param>
    /// <exception cref="ArgumentNullException">Thrown when any of the arguments are null.</exception>
    public LogicalAndExpressionParseNode(
        ExpressionParseNode left,
        ExpressionParseNode right,
        Token start,
        IEnumerable<CommentToken> preceedingComments)
        : base(start, preceedingComments)
    {
        this.Left = left ?? throw new ArgumentNullException(nameof(left));
        this.Right = right ?? throw new ArgumentNullException(nameof(right));
    }

    /// <summary>
    /// Gets the left operand of the logical AND expression.
    /// </summary>
    public ExpressionParseNode Left { get; }

    /// <summary>
    /// Gets the right operand of the logical AND expression.
    /// </summary>
    public ExpressionParseNode Right { get; }
}