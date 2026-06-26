// <copyright file="ReturnStatementParseNode.cs" company="Jon Rowlett">
// Copyright (c) Jon Rowlett. All rights reserved.
// </copyright>

namespace OpenDraft.Lang;

/// <summary>
/// Represents a parse node for a return statement.
/// </summary>
public class ReturnStatementParseNode : StatementParseNode
{
    /// <summary>
    /// Initializes a new instance of the <see cref="ReturnStatementParseNode"/> class.
    /// </summary>
    /// <param name="expression">The expression to return, or null if there is no expression.</param>
    /// <param name="start">The starting token of the return statement.</param>
    /// <param name="precedingComments">The comments preceding the return statement.</param>
    public ReturnStatementParseNode(
        ExpressionParseNode? expression,
        Token start,
        IEnumerable<CommentToken> precedingComments)
        : base(start, precedingComments)
    {
        this.Expression = expression;
    }

    /// <summary>
    /// Gets the expression to return, or null if there is no expression.
    /// </summary>
    public ExpressionParseNode? Expression { get; }
}