// <copyright file="ConditionalExpressionParseNode.cs" company="Jon Rowlett">
// Copyright (c) Jon Rowlett. All rights reserved.
// </copyright>

namespace OpenDraft.Lang;

/// <summary>
/// Represents a conditional expression (ternary operator) parse node.
/// </summary>
public class ConditionalExpressionParseNode : ExpressionParseNode
{
    /// <summary>
    /// Initializes a new instance of the <see cref="ConditionalExpressionParseNode"/> class.
    /// </summary>
    /// <param name="condition">The condition expression of the conditional expression.</param>
    /// <param name="trueExpression">The expression evaluated when the condition is true.</param>
    /// <param name="falseExpression">The expression evaluated when the condition is false.</param>
    /// <param name="start">The starting token of the conditional expression.</param>
    /// <param name="preceedingComments">The comments preceding the conditional expression.</param>
    /// <exception cref="ArgumentNullException">Thrown when any of the arguments are null.</exception>
    public ConditionalExpressionParseNode(
        ExpressionParseNode condition,
        ExpressionParseNode trueExpression,
        ExpressionParseNode falseExpression,
        Token start,
        IEnumerable<CommentToken> preceedingComments)
        : base(start, preceedingComments)
    {
        this.Condition = condition ?? throw new ArgumentNullException(nameof(condition));
        this.TrueExpression = trueExpression ?? throw new ArgumentNullException(nameof(trueExpression));
        this.FalseExpression = falseExpression ?? throw new ArgumentNullException(nameof(falseExpression));
    }

    /// <summary>
    /// Gets the condition expression of the conditional expression.
    /// </summary>
    public ExpressionParseNode Condition { get; }

    /// <summary>
    /// Gets the expression evaluated when the condition is true.
    /// </summary>
    public ExpressionParseNode TrueExpression { get; }

    /// <summary>
    /// Gets the expression evaluated when the condition is false.
    /// </summary>
    public ExpressionParseNode FalseExpression { get; }
}