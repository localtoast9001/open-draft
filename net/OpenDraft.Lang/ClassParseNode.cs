// <copyright file="ClassParseNode.cs" company="Jon Rowlett">
// Copyright (c) Jon Rowlett. All rights reserved.
// </copyright>

namespace OpenDraft.Lang;

/// <summary>
/// Represents a parse node for a class declaration.
/// </summary>
public class ClassParseNode : ProgramElementParseNode
{
    /// <summary>
    /// Initializes a new instance of the <see cref="ClassParseNode"/> class.
    /// </summary>
    /// <param name="name">The name of the class.</param>
    /// <param name="start">The starting token of the class declaration.</param>
    /// <param name="precedingComments">The comments preceding the class declaration.</param>
    public ClassParseNode(
        string name,
        Token start,
        IEnumerable<CommentToken> precedingComments)
        : base(start, precedingComments)
    {
        this.Name = name ?? throw new ArgumentNullException(nameof(name));
    }

    /// <summary>
    /// Gets the name of the class.
    /// </summary>
    public string Name { get; }
}