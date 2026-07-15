// <copyright file="UnaryExpressionParseNode.cs" company="Jon Rowlett">
// Copyright (c) Jon Rowlett. All rights reserved.
// </copyright>

namespace OpenDraft.Lang;

/// <summary>
/// Represents a unary operator.
/// </summary>
public enum UnaryOperator
{
    /// <summary>
    /// Negates the value of the operand.
    /// </summary>
    Negate,

    /// <summary>
    /// Performs a logical NOT operation on the operand.
    /// </summary>
    LogicalNot,

    /// <summary>
    /// Performs a bitwise NOT operation on the operand.
    /// </summary>
    BitwiseNot,
}

/// <summary>
/// Represents a unary expression parse node.
/// </summary>
public class UnaryExpressionParseNode : ExpressionParseNode
{
    /// <summary>
    /// Initializes a new instance of the <see cref="UnaryExpressionParseNode"/> class.
    /// </summary>
    /// <param name="operand">The operand of the unary expression.</param>
    /// <param name="operator">The unary operator.</param>
    /// <param name="start">The starting token of the expression.</param>
    /// <param name="precedingComments">The comments preceding the expression.</param>
    /// <exception cref="ArgumentNullException">Thrown if <paramref name="operand"/> is <c>null</c>.</exception>
    public UnaryExpressionParseNode(
        ExpressionParseNode operand,
        UnaryOperator @operator,
        Token start,
        IEnumerable<CommentToken> precedingComments)
        : base(start, precedingComments)
    {
        this.Operand = operand ?? throw new ArgumentNullException(nameof(operand));
        this.Operator = @operator;
    }

    /// <summary>
    /// Gets the operand of the unary expression.
    /// </summary>
    public ExpressionParseNode Operand { get; }

    /// <summary>
    /// Gets the unary operator.
    /// </summary>
    public UnaryOperator Operator { get; }
}