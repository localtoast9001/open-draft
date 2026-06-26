// <copyright file="ProgramElementParseNode.cs" company="Jon Rowlett">
// Copyright (c) Jon Rowlett. All rights reserved.
// </copyright>

namespace OpenDraft.Lang;

/// <summary>
/// Represents a parse node for a program element that can appear in the main body of the program file or within a namespace.
/// </summary>
public abstract class ProgramElementParseNode : ParseNode
{
    /// <summary>
    /// Initializes a new instance of the <see cref="ProgramElementParseNode"/> class.
    /// </summary>
    /// <param name="start">The starting token of the program element.</param>
    /// <param name="precedingComments">The comments preceding the program element.</param>
    protected ProgramElementParseNode(Token start, IEnumerable<CommentToken> precedingComments)
    : base(start, precedingComments)
    {
    }
}