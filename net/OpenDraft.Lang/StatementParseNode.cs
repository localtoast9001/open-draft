// <copyright file="StatementParseNode.cs" company="Jon Rowlett">
// Copyright (c) Jon Rowlett. All rights reserved.
// </copyright>

namespace OpenDraft.Lang;

/// <summary>
/// Represents a statement in the language.
/// </summary>
/// <remarks>
/// Statements may appear interspersed with other program elements within the program.
/// </remarks>
public abstract class StatementParseNode : ProgramElementParseNode
{
    /// <summary>
    /// Initializes a new instance of the <see cref="StatementParseNode"/> class.
    /// </summary>
    /// <param name="start">The starting token of the statement.</param>
    /// <param name="precedingComments">The comments preceding the statement.</param>
    protected StatementParseNode(Token start, IEnumerable<CommentToken> precedingComments)
        : base(start, precedingComments)
    {
    }
}