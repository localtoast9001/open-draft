// <copyright file="NullExpressionParseNode.cs" company="Jon Rowlett">
// Copyright (c) Jon Rowlett. All rights reserved.
// </copyright>

namespace OpenDraft.Lang;

/// <summary>
/// Represents a null expression parse node.
/// </summary>
public class NullExpressionParseNode : ExpressionParseNode
{
    /// <summary>
    /// Initializes a new instance of the <see cref="NullExpressionParseNode"/> class.
    /// </summary>
    /// <param name="start">The starting token of the expression.</param>
    /// <param name="precedingComments">The comments preceding the expression.</param>
    public NullExpressionParseNode(
        Token start,
        IEnumerable<CommentToken> precedingComments)
        : base(start, precedingComments)
    {
    }
}