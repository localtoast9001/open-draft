// <copyright file="CallStatementParseNode.cs" company="Jon Rowlett">
// Copyright (c) Jon Rowlett. All rights reserved.
// </copyright>

namespace OpenDraft.Lang;

/// <summary>
/// Represents a call statement in the parse tree.
/// </summary>
public class CallStatementParseNode : StatementParseNode
{
    /// <summary>
    /// Initializes a new instance of the <see cref="CallStatementParseNode"/> class.
    /// </summary>
    /// <param name="target">The target of the call.</param>
    /// <param name="arguments">Arguments to the call.</param>
    /// <param name="start">The starting token of the call statement.</param>
    /// <param name="precedingComments">Comments preceding the call statement.</param>
    public CallStatementParseNode(
        ReferenceExpressionParseNode target,
        IEnumerable<ArgumentParseNode> arguments,
        Token start,
        IEnumerable<CommentToken> precedingComments)
        : base(start, precedingComments)
    {
        this.Target = target;
        this.Arguments = arguments.ToList().AsReadOnly();
    }

    /// <summary>
    /// Gets the target to call.
    /// </summary>
    public ReferenceExpressionParseNode Target { get; }

    /// <summary>
    /// Gets the arguments for the call.
    /// </summary>
    public IReadOnlyList<ArgumentParseNode> Arguments { get; }

    /// <summary>
    /// Creates a call statement from a call expression.
    /// </summary>
    /// <param name="source">The call expression to convert.</param>
    /// <returns>A new <see cref="CallStatementParseNode"/> representing the call statement.</returns>
    public static CallStatementParseNode FromCallExpression(
        CallExpressionParseNode source) =>
        new CallStatementParseNode(source.Target, source.Arguments, source.Start, source.PrecedingComments);
}