// <copyright file="ForStatementParseNode.cs" company="Jon Rowlett">
// Copyright (c) Jon Rowlett. All rights reserved.
// </copyright>

namespace OpenDraft.Lang;

/// <summary>
/// Represents a for loop statement in the parse tree.
/// </summary>
public class ForStatementParseNode : StatementParseNode
{
    /// <summary>
    /// Initializes a new instance of the <see cref="ForStatementParseNode"/> class.
    /// </summary>
    /// <param name="conditions">The list of conditions for the for loop.</param>
    /// <param name="body">The body of the for loop.</param>
    /// <param name="token">The token representing the for statement.</param>
    /// <param name="precedingComments">The comments preceding the for statement.</param>
    public ForStatementParseNode(
        IReadOnlyList<ForConditionParseNode> conditions,
        StatementParseNode body,
        Token token,
        IEnumerable<CommentToken> precedingComments)
        : base(token, precedingComments)
    {
        this.Conditions = conditions.ToList().AsReadOnly();
        this.Body = body ?? throw new ArgumentNullException(nameof(body));
    }

    /// <summary>
    /// Gets the list of conditions for the for loop.
    /// </summary>
    public IReadOnlyList<ForConditionParseNode> Conditions { get; }

    /// <summary>
    /// Gets the body of the for loop.
    /// </summary>
    public StatementParseNode Body { get; }
}