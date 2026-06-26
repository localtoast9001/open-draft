// <copyright file="IfStatementParseNode.cs" company="Jon Rowlett">
// Copyright (c) Jon Rowlett. All rights reserved.
// </copyright>

namespace OpenDraft.Lang;

/// <summary>
/// Represents a parse node for an if statement.
/// </summary>
public class IfStatementParseNode : StatementParseNode
{
    /// <summary>
    /// Initializes a new instance of the <see cref="IfStatementParseNode"/> class.
    /// </summary>
    /// <param name="condition">The condition expression of the if statement.</param>
    /// <param name="thenStatement">The statement to execute if the condition is true.</param>
    /// <param name="elseStatement">The statement to execute if the condition is false.</param>
    /// <param name="start">The starting token of the if statement.</param>
    /// <param name="precedingComments">The comments preceding the if statement.</param>
    public IfStatementParseNode(
        ExpressionParseNode condition,
        StatementParseNode thenStatement,
        StatementParseNode? elseStatement,
        Token start,
        IEnumerable<CommentToken> precedingComments)
        : base(start, precedingComments)
    {
        this.Condition = condition;
        this.ThenStatement = thenStatement;
        this.ElseStatement = elseStatement;
    }

    /// <summary>
    /// Gets the condition expression of the if statement.
    /// </summary>
    public ExpressionParseNode Condition { get; }

    /// <summary>
    /// Gets the statement to execute if the condition is true.
    /// </summary>
    public StatementParseNode ThenStatement { get; }

    /// <summary>
    /// Gets the statement to execute if the condition is false.
    /// </summary>
    public StatementParseNode? ElseStatement { get; }
}