// <copyright file="BreakStatementParseNode.cs" company="Jon Rowlett">
// Copyright (c) Jon Rowlett. All rights reserved.
// </copyright>

namespace OpenDraft.Lang;

/// <summary>
/// Represents a parse node for a break statement.
/// </summary>
public class BreakStatementParseNode : StatementParseNode
{
    /// <summary>
    /// Initializes a new instance of the <see cref="BreakStatementParseNode"/> class.
    /// </summary>
    /// <param name="start">The starting token of the break statement.</param>
    /// <param name="precedingComments">The comments preceding the break statement.</param>
    public BreakStatementParseNode(Token start, IEnumerable<CommentToken> precedingComments)
        : base(start, precedingComments)
    {
    }
}