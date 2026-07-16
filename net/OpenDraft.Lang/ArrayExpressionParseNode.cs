// <copyright file="ArrayExpressionParseNode.cs" company="Jon Rowlett">
// Copyright (c) Jon Rowlett. All rights reserved.
// </copyright>

namespace OpenDraft.Lang;

/// <summary>
/// Represents an array expression parse node.
/// </summary>
public class ArrayExpressionParseNode : ExpressionParseNode
{
    /// <summary>
    /// Initializes a new instance of the <see cref="ArrayExpressionParseNode"/> class.
    /// </summary>
    /// <param name="elements">The elements of the array expression.</param>
    /// <param name="start">The starting token of the expression.</param>
    /// <param name="precedingComments">The comments preceding the expression.</param>
    public ArrayExpressionParseNode(
        IEnumerable<IEnumerable<ExpressionParseNode>> elements,
        Token start,
        IEnumerable<CommentToken> precedingComments)
        : base(start, precedingComments)
    {
        this.Elements = elements.Select(e => e.ToList().AsReadOnly()).ToList().AsReadOnly();
    }

    /// <summary>
    /// Gets the elements of the array expression.
    /// </summary>
    public IReadOnlyList<IReadOnlyList<ExpressionParseNode>> Elements { get; }
}