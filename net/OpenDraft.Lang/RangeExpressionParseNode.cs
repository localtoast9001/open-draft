// <copyright file="RangeExpressionParseNode.cs" company="Jon Rowlett">
// Copyright (c) Jon Rowlett. All rights reserved.
// </copyright>

namespace OpenDraft.Lang;

/// <summary>
/// Represents a range expression parse node.
/// </summary>
public class RangeExpressionParseNode : ExpressionParseNode
{
    /// <summary>
    /// Initializes a new instance of the <see cref="RangeExpressionParseNode"/> class.
    /// </summary>
    /// <param name="from">The starting expression of the range.</param>
    /// <param name="to">The ending expression of the range.</param>
    /// <param name="start">The starting token of the range expression.</param>
    /// <param name="precedingComments">The comments preceding the range expression.</param>
    /// <exception cref="ArgumentNullException">Thrown if <paramref name="from"/> or <paramref name="to"/> is <c>null</c>.</exception>
    public RangeExpressionParseNode(
        ExpressionParseNode from,
        ExpressionParseNode to,
        Token start,
        IEnumerable<CommentToken> precedingComments)
        : base(start, precedingComments)
    {
        this.From = from ?? throw new ArgumentNullException(nameof(from));
        this.To = to ?? throw new ArgumentNullException(nameof(to));
    }

    /// <summary>
    /// Gets the starting expression of the range.
    /// </summary>
    public ExpressionParseNode From { get; }

    /// <summary>
    /// Gets the ending expression of the range.
    /// </summary>
    public ExpressionParseNode To { get; }
}