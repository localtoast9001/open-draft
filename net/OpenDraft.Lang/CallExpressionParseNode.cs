// <copyright file="CallExpressionParseNode.cs" company="Jon Rowlett">
// Copyright (c) Jon Rowlett. All rights reserved.
// </copyright>

namespace OpenDraft.Lang;

/// <summary>
/// Represents a call expression in the language.
/// </summary>
public class CallExpressionParseNode : ReferenceExpressionParseNode
{
    /// <summary>
    /// Initializes a new instance of the <see cref="CallExpressionParseNode"/> class.
    /// </summary>
    /// <param name="target">The target of the call expression.</param>
    /// <param name="arguments">The arguments of the call expression.</param>
    /// <param name="start">The starting token of the call expression.</param>
    /// <param name="precedingComments">The comments preceding the call expression.</param>
    public CallExpressionParseNode(
        ReferenceExpressionParseNode target,
        IEnumerable<ArgumentParseNode> arguments,
        Token start,
        IEnumerable<CommentToken> precedingComments)
        : base(start, precedingComments)
    {
        this.Target = target ?? throw new ArgumentNullException(nameof(target));
        this.Arguments = (arguments ?? throw new ArgumentNullException(nameof(arguments))).ToList();
    }

    /// <summary>
    /// Gets the target of the call expression.
    /// </summary>
    public ReferenceExpressionParseNode Target { get; }

    /// <summary>
    /// Gets the arguments of the call expression.
    /// </summary>
    public IReadOnlyList<ArgumentParseNode> Arguments { get; }
}