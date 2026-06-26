// <copyright file="EnumMemberParseNode.cs" company="Jon Rowlett">
// Copyright (c) Jon Rowlett. All rights reserved.
// </copyright>

namespace OpenDraft.Lang;

/// <summary>
/// Represents a member of an enum type, which consists of a name and an optional value.
/// </summary>
public class EnumMemberParseNode : ParseNode
{
    /// <summary>
    /// Initializes a new instance of the <see cref="EnumMemberParseNode"/> class.
    /// </summary>
    /// <param name="name">The name of the enum member.</param>
    /// <param name="value">The value of the enum member, or null if no value was specified.</param>
    /// <param name="start">The starting token of the enum member.</param>
    /// <param name="precedingComments">The comments preceding the enum member.</param>
    public EnumMemberParseNode(
        string name,
        long? value,
        Token start,
        IEnumerable<CommentToken> precedingComments)
        : base(start, precedingComments)
    {
        this.Name = name ?? throw new ArgumentNullException(nameof(name));
        this.Value = value;
    }

    /// <summary>
    /// Gets the name of the enum member.
    /// </summary>
    public string Name { get; }

    /// <summary>
    /// Gets the value of the enum member, or null if no value was specified. If no value was specified, the value of this member will be determined by the type system based on the values of the other members of the enum.
    /// </summary>
    public long? Value { get; }
}