// <copyright file="NamespaceParseNode.cs" company="Jon Rowlett">
// Copyright (c) Jon Rowlett. All rights reserved.
// </copyright>

namespace OpenDraft.Lang;

/// <summary>
/// Represents a parse node for a namespace declaration, which can contain classes, interfaces, enums, and other namespaces.
/// </summary>
public class NamespaceParseNode : ProgramElementParseNode
{
    /// <summary>
    /// Initializes a new instance of the <see cref="NamespaceParseNode"/> class.
    /// </summary>
    /// <param name="namespaceMembers">The members of the namespace.</param>
    /// <param name="start">The starting token of the namespace declaration.</param>
    /// <param name="precedingComments">The comments preceding the namespace declaration.</param>
    public NamespaceParseNode(
        IEnumerable<ProgramElementParseNode> namespaceMembers,
        Token start,
        IEnumerable<CommentToken> precedingComments)
        : base(start, precedingComments)
    {
        this.NamespaceMembers = namespaceMembers.ToList().AsReadOnly();
    }

    /// <summary>
    /// Gets the members of the namespace, which can include classes, interfaces, enums, and other namespaces.
    /// </summary>
    public IReadOnlyList<ProgramElementParseNode> NamespaceMembers { get; }
}