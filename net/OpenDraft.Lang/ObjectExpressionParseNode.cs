// <copyright file="ObjectExpressionParseNode.cs" company="Jon Rowlett">
// Copyright (c) Jon Rowlett. All rights reserved.
// </copyright>

namespace OpenDraft.Lang;

/// <summary>
/// Represents an object expression in the language.
/// </summary>
public class ObjectExpressionParseNode : ExpressionParseNode
{
    /// <summary>
    /// Initializes a new instance of the <see cref="ObjectExpressionParseNode"/> class.
    /// </summary>
    /// <param name="members">The members of the object expression.</param>
    /// <param name="start">The starting token of the object expression.</param>
    /// <param name="precedingComments">The comments preceding the object expression.</param>
    public ObjectExpressionParseNode(
        IReadOnlyList<ObjectMemberParseNode> members,
        Token start,
        IEnumerable<CommentToken> precedingComments)
        : base(start, precedingComments)
    {
        this.Members = members?.ToList().AsReadOnly() ?? throw new ArgumentNullException(nameof(members));
    }

    /// <summary>
    /// Gets the members of the object expression.
    /// </summary>
    public IReadOnlyList<ObjectMemberParseNode> Members { get; }
}