// <copyright file="AddExpressionParseNode.cs" company="Jon Rowlett">
// Copyright (c) Jon Rowlett. All rights reserved.
// </copyright>

namespace OpenDraft.Lang;

/// <summary>
/// Represents an addition or subtraction expression parse node.
/// </summary>
public class AddExpressionParseNode : ExpressionParseNode
{
    /// <summary>
    /// Initializes a new instance of the <see cref="AddExpressionParseNode"/> class.
    /// </summary>
    /// <param name="left">The left operand of the addition or subtraction expression.</param>
    /// <param name="right">The right operand of the addition or subtraction expression.</param>
    /// <param name="isSubtraction">Indicates whether the expression is a subtraction.</param>
    /// <param name="start">The starting token of the expression.</param>
    /// <param name="precedingComments">The comments preceding the expression.</param>
    /// <exception cref="ArgumentNullException">Thrown if <paramref name="left"/> or <paramref name="right"/> is <c>null</c>.</exception>
    public AddExpressionParseNode(
        ExpressionParseNode left,
        ExpressionParseNode right,
        bool isSubtraction,
        Token start,
        IEnumerable<CommentToken> precedingComments)
        : base(start, precedingComments)
    {
        this.Left = left ?? throw new ArgumentNullException(nameof(left));
        this.Right = right ?? throw new ArgumentNullException(nameof(right));
        this.IsSubtraction = isSubtraction;
    }

    /// <summary>
    /// Gets the left operand of the addition or subtraction expression.
    /// </summary>
    public ExpressionParseNode Left { get; }

    /// <summary>
    /// Gets the right operand of the addition or subtraction expression.
    /// </summary>
    public ExpressionParseNode Right { get; }

    /// <summary>
    /// Gets a value indicating whether the expression is a subtraction.
    /// </summary>
    public bool IsSubtraction { get; }
}