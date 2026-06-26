// <copyright file="EnumParseNode.cs" company="Jon Rowlett">
// Copyright (c) Jon Rowlett. All rights reserved.
// </copyright>

namespace OpenDraft.Lang;

/// <summary>
/// Represents an enum type declaration, which consists of a name and a list of members. Each member has a name and an optional value. If a member does not have a value, its value will be determined by the type system based on the values of the other members of the enum.
/// </summary>
public class EnumParseNode : ProgramElementParseNode
{
    /// <summary>
    /// Initializes a new instance of the <see cref="EnumParseNode"/> class.
    /// </summary>
    /// <param name="name">The name of the enum type.</param>
    /// <param name="members">The members of the enum type.</param>
    /// <param name="start">The starting token of the enum type.</param>
    /// <param name="precedingComments">The comments preceding the enum type.</param>
    /// <exception cref="ArgumentNullException">
    /// Thrown if <paramref name="name"/> or <paramref name="members"/> is null.
    /// </exception>
    public EnumParseNode(
        string name,
        IEnumerable<EnumMemberParseNode> members,
        Token start,
        IEnumerable<CommentToken> precedingComments)
        : base(start, precedingComments)
    {
        this.Name = name ?? throw new ArgumentNullException(nameof(name));
        this.Members = members.ToList().AsReadOnly();
    }

    /// <summary>
    /// Gets the name of the enum type.
    /// </summary>
    public string Name { get; }

    /// <summary>
    /// Gets the members of the enum type. Each member has a name and an optional value. If a member does not have a value, its value will be determined by the type system based on the values of the other members of the enum.
    /// </summary>
    public IReadOnlyList<EnumMemberParseNode> Members { get; }
}