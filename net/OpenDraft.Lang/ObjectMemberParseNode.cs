// <copyright file="ObjectMemberParseNode.cs" company="Jon Rowlett">
// Copyright (c) Jon Rowlett. All rights reserved.
// </copyright>
namespace OpenDraft.Lang;

/// <summary>
/// Represents a member of an object expression.
/// </summary>
/// <seealso cref="ObjectExpressionParseNode"/>
public class ObjectMemberParseNode : ParseNode
{
    /// <summary>
    /// Initializes a new instance of the <see cref="ObjectMemberParseNode"/> class.
    /// </summary>
    /// <param name="name">The name of the object member.</param>
    /// <param name="value">The value of the object member.</param>
    /// <param name="start">The starting token of the object member.</param>
    /// <param name="precedingComments">The comments preceding the object member.</param>
    public ObjectMemberParseNode(
        string name,
        ExpressionParseNode value,
        Token start,
        IEnumerable<CommentToken> precedingComments)
        : base(start, precedingComments)
    {
        this.Name = name ?? throw new ArgumentNullException(nameof(name));
        this.Value = value ?? throw new ArgumentNullException(nameof(value));
    }

    /// <summary>
    /// Gets the name of the object member.
    /// </summary>
    public string Name { get; }

    /// <summary>
    /// Gets the value of the object member.
    /// </summary>
    public ExpressionParseNode Value { get; }
}