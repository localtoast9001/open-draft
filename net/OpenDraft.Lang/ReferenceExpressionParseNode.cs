// <copyright file="ReferenceExpressionParseNode.cs" company="Jon Rowlett">
// Copyright (c) Jon Rowlett. All rights reserved.
// </copyright>

namespace OpenDraft.Lang;

/// <summary>
/// Represents a reference expression in the language.
/// </summary>
public abstract class ReferenceExpressionParseNode : ExpressionParseNode
{
    /// <summary>
    /// Initializes a new instance of the <see cref="ReferenceExpressionParseNode"/> class.
    /// </summary>
    /// <param name="start">The starting token of the reference expression.</param>
    /// <param name="precedingComments">The comments preceding the reference expression.</param>
    protected ReferenceExpressionParseNode(
        Token start,
        IEnumerable<CommentToken> precedingComments)
        : base(start, precedingComments)
    {
    }

    /// <summary>
    /// Attempts to convert the expression into a possible type reference parse node.
    /// </summary>
    /// <returns>A <see cref="TypeReferenceParseNode"/> if the conversion is possible; otherwise, <c>null</c>.</returns>
    public virtual TypeReferenceParseNode? ToTypeReference()
    {
        return null;
    }
}