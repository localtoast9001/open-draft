// <copyright file="EqualityExpressionParseNode.cs" company="Jon Rowlett">
// Copyright (c) Jon Rowlett. All rights reserved.
// </copyright>

namespace OpenDraft.Lang;

/// <summary>
/// Represents an equality or inequality expression parse node.
/// </summary>
public class EqualityExpressionParseNode : ExpressionParseNode
{
    /// <summary>
    /// Initializes a new instance of the <see cref="EqualityExpressionParseNode"/> class.
    /// </summary>
    /// <param name="left">The left operand of the equality or inequality expression.</param>
    /// <param name="right">The right operand of the equality or inequality expression.</param>
    /// <param name="isInequality">Indicates whether the expression is an inequality.</param>
    /// <param name="start">The starting token of the equality or inequality expression.</param>
    /// <param name="preceedingComments">The comments preceding the equality or inequality expression.</param>
    /// <exception cref="ArgumentNullException">Thrown when any of the arguments are null.</exception>
    public EqualityExpressionParseNode(
        ExpressionParseNode left,
        ExpressionParseNode right,
        bool isInequality,
        Token start,
        IEnumerable<CommentToken> preceedingComments)
        : base(start, preceedingComments)
    {
        this.Left = left ?? throw new ArgumentNullException(nameof(left));
        this.Right = right ?? throw new ArgumentNullException(nameof(right));
        this.IsInequality = isInequality;
    }

    /// <summary>
    /// Gets the left operand of the equality or inequality expression.
    /// </summary>
    public ExpressionParseNode Left { get; }

    /// <summary>
    /// Gets the right operand of the equality or inequality expression.
    /// </summary>
    public ExpressionParseNode Right { get; }

    /// <summary>
    /// Gets a value indicating whether the expression is an inequality.
    /// </summary>
    public bool IsInequality { get; }
}