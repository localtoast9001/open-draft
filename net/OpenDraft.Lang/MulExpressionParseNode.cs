// <copyright file="MulExpressionParseNode.cs" company="Jon Rowlett">
// Copyright (c) Jon Rowlett. All rights reserved.
// </copyright>

namespace OpenDraft.Lang;

/// <summary>
/// Represents a multiplication, division, or modulo operator.
/// </summary>
public enum MulOperator
{
    /// <summary>
    /// Represents the multiplication operator.
    /// </summary>
    Multiply,

    /// <summary>
    /// Represents the division operator.
    /// </summary>
    Divide,

    /// <summary>
    /// Represents the modulo operator.
    /// </summary>
    Modulo,
}

/// <summary>
/// Represents a multiplication, division, or modulo expression parse node.
/// </summary>
public class MulExpressionParseNode : ExpressionParseNode
{
    /// <summary>
    /// Initializes a new instance of the <see cref="MulExpressionParseNode"/> class.
    /// </summary>
    /// <param name="left">The left operand of the multiplication, division, or modulo expression.</param>
    /// <param name="right">The right operand of the multiplication, division, or modulo expression.</param>
    /// <param name="operator">The operator of the multiplication, division, or modulo expression.</param>
    /// <param name="start">The starting token of the expression.</param>
    /// <param name="precedingComments">The comments preceding the expression.</param>
    /// <exception cref="ArgumentNullException">Thrown if <paramref name="left"/> or <paramref name="right"/> is <c>null</c>.</exception>
    public MulExpressionParseNode(
        ExpressionParseNode left,
        ExpressionParseNode right,
        MulOperator @operator,
        Token start,
        IEnumerable<CommentToken> precedingComments)
        : base(start, precedingComments)
    {
        this.Left = left ?? throw new ArgumentNullException(nameof(left));
        this.Right = right ?? throw new ArgumentNullException(nameof(right));
        this.Operator = @operator;
    }

    /// <summary>
    /// Gets the left operand of the multiplication, division, or modulo expression.
    /// </summary>
    public ExpressionParseNode Left { get; }

    /// <summary>
    /// Gets the right operand of the multiplication, division, or modulo expression.
    /// </summary>
    public ExpressionParseNode Right { get; }

    /// <summary>
    /// Gets the operator of the multiplication, division, or modulo expression.
    /// </summary>
    public MulOperator Operator { get; }
}