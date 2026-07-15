// <copyright file="RelationalExpressionParseNode.cs" company="Jon Rowlett">
// Copyright (c) Jon Rowlett. All rights reserved.
// </copyright>

namespace OpenDraft.Lang;

/// <summary>
/// Represents the relational operators for a relational expression.
/// </summary>
public enum RelationalOperator
{
    /// <summary>
    /// Strictly less than.
    /// </summary>
    LessThan,

    /// <summary>
    /// Less than or equal to.
    /// </summary>
    LessThanOrEqual,

    /// <summary>
    /// Strictly greater than.
    /// </summary>
    GreaterThan,

    /// <summary>
    /// Greater than or equal to.
    /// </summary>
    GreaterThanOrEqual,

    /// <summary>
    /// The left operand is in the set of values specified by the right operand.
    /// </summary>
    InSet,
}

/// <summary>
/// Represents a relational expression parse node.
/// </summary>
public class RelationalExpressionParseNode : ExpressionParseNode
{
    /// <summary>
    /// Initializes a new instance of the <see cref="RelationalExpressionParseNode"/> class.
    /// </summary>
    /// <param name="left">The left operand of the relational expression.</param>
    /// <param name="right">The right operand of the relational expression.</param>
    /// <param name="op">The relational operator.</param>
    /// <param name="start">The starting token of the expression.</param>
    /// <param name="precedingComments">The comments preceding the expression.</param>
    /// <exception cref="ArgumentNullException">Thrown if <paramref name="left"/> or <paramref name="right"/> is <c>null</c>.</exception>
    public RelationalExpressionParseNode(
        ExpressionParseNode left,
        ExpressionParseNode right,
        RelationalOperator op,
        Token start,
        IEnumerable<CommentToken> precedingComments)
        : base(start, precedingComments)
    {
        this.Left = left ?? throw new ArgumentNullException(nameof(left));
        this.Right = right ?? throw new ArgumentNullException(nameof(right));
        this.Operator = op;
    }

    /// <summary>
    /// Gets the left operand of the relational expression.
    /// </summary>
    public ExpressionParseNode Left { get; }

    /// <summary>
    /// Gets the right operand of the relational expression.
    /// </summary>
    public ExpressionParseNode Right { get; }

    /// <summary>
    /// Gets the relational operator.
    /// </summary>
    public RelationalOperator Operator { get; }
}