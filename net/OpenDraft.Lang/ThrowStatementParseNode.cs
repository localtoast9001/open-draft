// <copyright file="ThrowStatementParseNode.cs" company="Jon Rowlett">
// Copyright (c) Jon Rowlett. All rights reserved.
// </copyright>

namespace OpenDraft.Lang;

/// <summary>
/// Represents a throw statement in the syntax tree.
/// </summary>
public class ThrowStatementParseNode : StatementParseNode
{
    /// <summary>
    /// Initializes a new instance of the <see cref="ThrowStatementParseNode"/> class.
    /// </summary>
    /// <param name="expression">The expression being thrown.</param>
    /// <param name="token">The token representing the throw statement.</param>
    /// <param name="precedingComments">The comments preceding the throw statement.</param>
    public ThrowStatementParseNode(
        ExpressionParseNode expression,
        Token token,
        IEnumerable<CommentToken> precedingComments)
        : base(token, precedingComments)
    {
        this.Expression = expression ?? throw new ArgumentNullException(nameof(expression));
    }

    /// <summary>
    /// Gets the expression for the throw statement.
    /// </summary>
    public ExpressionParseNode Expression { get; }
}