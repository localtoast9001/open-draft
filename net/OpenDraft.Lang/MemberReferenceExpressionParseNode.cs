// <copyright file="MemberReferenceExpressionParseNode.cs" company="Jon Rowlett">
// Copyright (c) Jon Rowlett. All rights reserved.
// </copyright>

namespace OpenDraft.Lang;

/// <summary>
/// Represents a member reference expression in the language.
/// </summary>
public class MemberReferenceExpressionParseNode : ReferenceExpressionParseNode
{
    /// <summary>
    /// Initializes a new instance of the <see cref="MemberReferenceExpressionParseNode"/> class.
    /// </summary>
    /// <param name="target">The target of the member reference.</param>
    /// <param name="name">The name of the member being referenced.</param>
    /// <param name="start">The starting token of the member reference.</param>
    /// <param name="precedingComments">The comments preceding the member reference.</param>
    public MemberReferenceExpressionParseNode(
        ReferenceExpressionParseNode target,
        string name,
        Token start,
        IEnumerable<CommentToken> precedingComments)
        : base(start, precedingComments)
    {
        this.Target = target ?? throw new ArgumentNullException(nameof(target));
        this.Name = name ?? throw new ArgumentNullException(nameof(name));
    }

    /// <summary>
    /// Gets the target of the member reference.
    /// </summary>
    public ReferenceExpressionParseNode Target { get; }

    /// <summary>
    /// Gets the name of the member being referenced.
    /// </summary>
    public string Name { get; }
}