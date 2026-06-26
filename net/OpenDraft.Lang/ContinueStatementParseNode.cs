// <copyright file="ContinueStatementParseNode.cs" company="Jon Rowlett">
// Copyright (c) Jon Rowlett. All rights reserved.
// </copyright>

namespace OpenDraft.Lang;

/// <summary>
/// Represents a parse node for a continue statement.
/// </summary>
public class ContinueStatementParseNode : StatementParseNode
{
    /// <summary>
    /// Initializes a new instance of the <see cref="ContinueStatementParseNode"/> class.
    /// </summary>
    /// <param name="start">The starting token of the continue statement.</param>
    /// <param name="precedingComments">The comments preceding the continue statement.</param>
    public ContinueStatementParseNode(Token start, IEnumerable<CommentToken> precedingComments)
        : base(start, precedingComments)
    {
    }
}