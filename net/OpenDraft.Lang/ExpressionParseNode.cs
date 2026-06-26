// <copyright file="ExpressionParseNode.cs" company="Jon Rowlett">
// Copyright (c) Jon Rowlett. All rights reserved.
// </copyright>

namespace OpenDraft.Lang;

/// <summary>
/// Represents an expression in the language.
/// </summary>
public abstract class ExpressionParseNode : ParseNode
{
    /// <summary>
    /// Initializes a new instance of the <see cref="ExpressionParseNode"/> class.
    /// </summary>
    /// <param name="start">The starting token of the expression.</param>
    /// <param name="precedingComments">The comments preceding the expression.</param>
    protected ExpressionParseNode(Token start, IEnumerable<CommentToken> precedingComments)
        : base(start, precedingComments)
    {
    }
}