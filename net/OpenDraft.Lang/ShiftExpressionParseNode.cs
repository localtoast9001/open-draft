// <copyright file="ShiftExpressionParseNode.cs" company="Jon Rowlett">
// Copyright (c) Jon Rowlett. All rights reserved.
// </copyright>

namespace OpenDraft.Lang;

/// <summary>
/// Represents the shift operators for a shift expression.
/// </summary>
public enum ShiftOperator
{
    /// <summary>
    /// Left shift operator.
    /// </summary>
    LeftShift,

    /// <summary>
    /// Right shift operator.
    /// </summary>
    RightShift,
}

/// <summary>
/// Represents a shift expression parse node.
/// </summary>
public class ShiftExpressionParseNode : ExpressionParseNode
{
    /// <summary>
    /// Initializes a new instance of the <see cref="ShiftExpressionParseNode"/> class.
    /// </summary>
    /// <param name="left">The left operand of the shift expression.</param>
    /// <param name="right">The right operand of the shift expression.</param>
    /// <param name="op">The shift operator.</param>
    /// <param name="start">The starting token of the expression.</param>
    /// <param name="precedingComments">The comments preceding the expression.</param>
    /// <exception cref="ArgumentNullException">Thrown if <paramref name="left"/> or <paramref name="right"/> is <c>null</c>.</exception>
    public ShiftExpressionParseNode(
        ExpressionParseNode left,
        ExpressionParseNode right,
        ShiftOperator op,
        Token start,
        IEnumerable<CommentToken> precedingComments)
        : base(start, precedingComments)
    {
        this.Left = left ?? throw new ArgumentNullException(nameof(left));
        this.Right = right ?? throw new ArgumentNullException(nameof(right));
        this.Operator = op;
    }

    /// <summary>
    /// Gets the left operand of the shift expression.
    /// </summary>
    public ExpressionParseNode Left { get; }

    /// <summary>
    /// Gets the right operand of the shift expression.
    /// </summary>
    public ExpressionParseNode Right { get; }

    /// <summary>
    /// Gets the shift operator.
    /// </summary>
    public ShiftOperator Operator { get; }
}