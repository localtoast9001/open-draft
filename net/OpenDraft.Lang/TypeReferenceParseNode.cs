// <copyright file="TypeReferenceParseNode.cs" company="Jon Rowlett">
// Copyright (c) Jon Rowlett. All rights reserved.
// </copyright>

namespace OpenDraft.Lang;

/// <summary>
/// Represents a reference to a type, such as in a variable declaration or a function return type.
/// </summary>
public class TypeReferenceParseNode : ParseNode
{
    /// <summary>
    /// Initializes a new instance of the <see cref="TypeReferenceParseNode"/> class.
    /// </summary>
    /// <param name="names">The names that make up the type reference.</param>
    /// <param name="start">The starting token of the type reference.</param>
    /// <param name="precedingComments">The comments preceding the type reference.</param>
    public TypeReferenceParseNode(
        IEnumerable<string> names,
        Token start,
        IEnumerable<CommentToken> precedingComments)
        : base(start, precedingComments)
    {
        this.Names = names.ToList().AsReadOnly();
    }

    /// <summary>
    /// Gets the names that make up the type reference. For example, for a type reference like "System.Collections.Generic.List", this would contain ["System", "Collections", "Generic", "List"].
    /// </summary>
    public IReadOnlyList<string> Names { get; }
}