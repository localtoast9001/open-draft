// <copyright file="InterfaceMemberParseNode.cs" company="Jon Rowlett">
// Copyright (c) Jon Rowlett. All rights reserved.
// </copyright>

namespace OpenDraft.Lang;

/// <summary>
/// Represents a member of an interface in the language.
/// </summary>
public abstract class InterfaceMemberParseNode : ParseNode
{
    /// <summary>
    /// Initializes a new instance of the <see cref="InterfaceMemberParseNode"/> class.
    /// </summary>
    /// <param name="name">The name of the interface member.</param>
    /// <param name="start">The starting token of the interface member.</param>
    /// <param name="precedingComments">The comments preceding the interface member.</param>
    protected InterfaceMemberParseNode(
        string name,
        Token start,
        IEnumerable<CommentToken> precedingComments)
        : base(start, precedingComments)
    {
        this.Name = name ?? throw new ArgumentNullException(nameof(name));
    }

    /// <summary>
    /// Gets the name of the function.
    /// </summary>
    public string Name { get; }
}