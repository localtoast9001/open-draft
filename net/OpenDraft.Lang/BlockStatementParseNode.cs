// <copyright file="BlockStatementParseNode.cs" company="Jon Rowlett">
// Copyright (c) Jon Rowlett. All rights reserved.
// </copyright>

namespace OpenDraft.Lang;

/// <summary>
/// Represents a block statement in the language.
/// </summary>
public class BlockStatementParseNode : StatementParseNode
{
    /// <summary>
    /// Initializes a new instance of the <see cref="BlockStatementParseNode"/> class.
    /// </summary>
    /// <param name="statements">The statements contained within the block.</param>
    /// <param name="start">The starting token of the block.</param>
    /// <param name="precedingComments">The comments preceding the block.</param>
    public BlockStatementParseNode(
        IEnumerable<StatementParseNode> statements,
        Token start,
        IEnumerable<CommentToken> precedingComments)
        : base(start, precedingComments)
    {
        this.Statements = statements.ToList().AsReadOnly();
    }

    /// <summary>
    /// Gets the statements contained within the block.
    /// </summary>
    public IReadOnlyList<StatementParseNode> Statements { get; }
}