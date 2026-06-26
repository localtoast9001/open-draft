// <copyright file="InterfaceParseNode.cs" company="Jon Rowlett">
// Copyright (c) Jon Rowlett. All rights reserved.
// </copyright>

namespace OpenDraft.Lang;

/// <summary>
/// Represents a parse node for an interface declaration.
/// </summary>
public class InterfaceParseNode : ProgramElementParseNode
{
    /// <summary>
    /// Initializes a new instance of the <see cref="InterfaceParseNode"/> class.
    /// </summary>
    /// <param name="name">The name of the interface.</param>
    /// <param name="members">The members of the interface.</param>
    /// <param name="start">The starting token of the interface declaration.</param>
    /// <param name="precedingComments">The comments preceding the interface declaration.</param>
    /// <exception cref="ArgumentNullException">
    /// Thrown if <paramref name="name"/> or <paramref name="members"/> is <c>null</c>.
    /// </exception>
    public InterfaceParseNode(
        string name,
        IEnumerable<InterfaceMemberParseNode> members,
        Token start,
        IEnumerable<CommentToken> precedingComments)
        : base(start, precedingComments)
    {
        this.Name = name ?? throw new ArgumentNullException(nameof(name));
        this.Members = members?.ToList().AsReadOnly() ?? throw new ArgumentNullException(nameof(members));
    }

    /// <summary>
    /// Gets the name of the interface.
    /// </summary>
    public string Name { get; }

    /// <summary>
    /// Gets the members of the interface.
    /// </summary>
    public IReadOnlyList<InterfaceMemberParseNode> Members { get; }
}