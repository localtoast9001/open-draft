// <copyright file="ArgumentParseNode.cs" company="Jon Rowlett">
// Copyright (c) Jon Rowlett. All rights reserved.
// </copyright>

namespace OpenDraft.Lang;

/// <summary>
/// Represents an argument to a function call in the language.
/// </summary>
public class ArgumentParseNode : ParseNode
{
    /// <summary>
    /// Initializes a new instance of the <see cref="ArgumentParseNode"/> class.
    /// </summary>
    /// <param name="name">The name of the argument, if specified.</param>
    /// <param name="value">The value of the argument.</param>
    /// <param name="start">The starting token of the argument.</param>
    /// <param name="precedingComments">The comments preceding the argument.</param>
    /// <exception cref="ArgumentNullException">Thrown if <paramref name="value"/> is <c>null</c>.</exception>
    public ArgumentParseNode(
        string? name,
        ExpressionParseNode value,
        Token start,
        IEnumerable<CommentToken> precedingComments)
        : base(start, precedingComments)
    {
        this.Name = name;
        this.Value = value ?? throw new ArgumentNullException(nameof(value));
    }

    /// <summary>
    /// Gets the name of the argument, if specified.
    /// </summary>
    public string? Name { get; }

    /// <summary>
    /// Gets the value of the argument.
    /// </summary>
    public ExpressionParseNode Value { get; }
}