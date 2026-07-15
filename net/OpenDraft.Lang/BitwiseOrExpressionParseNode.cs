// <copyright file="BitwiseOrExpressionParseNode.cs" company="Jon Rowlett">
// Copyright (c) Jon Rowlett. All rights reserved.
// </copyright>

namespace OpenDraft.Lang;

/// <summary>
/// Represents a bitwise OR expression parse node.
/// </summary>
public class BitwiseOrExpressionParseNode : ExpressionParseNode
{
    /// <summary>
    /// Initializes a new instance of the <see cref="BitwiseOrExpressionParseNode"/> class.
    /// </summary>
    /// <param name="left">The left operand of the bitwise OR expression.</param>
    /// <param name="right">The right operand of the bitwise OR expression.</param>
    /// <param name="start">The starting token of the bitwise OR expression.</param>
    /// <param name="preceedingComments">The comments preceding the bitwise OR expression.</param>
    /// <exception cref="ArgumentNullException">Thrown when any of the arguments are null.</exception>
    public BitwiseOrExpressionParseNode(
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
    /// Gets the left operand of the bitwise OR expression.
    /// </summary>
    public ExpressionParseNode Left { get; }

    /// <summary>
    /// Gets the right operand of the bitwise OR expression.
    /// </summary>
    public ExpressionParseNode Right { get; }
}