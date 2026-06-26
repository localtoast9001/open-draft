// <copyright file="TraceStatementParseNode.cs" company="Jon Rowlett">
// Copyright (c) Jon Rowlett. All rights reserved.
// </copyright>

namespace OpenDraft.Lang;

/// <summary>
/// Defines the severity levels for trace statements.
/// </summary>
public enum TraceStatementSeverity
{
    /// <summary>
    /// Indicates an error severity level for trace statements.
    /// </summary>
    Error,

    /// <summary>
    /// Indicates a warning severity level for trace statements.
    /// </summary>
    Warn,

    /// <summary>
    /// Indicates an informational severity level for trace statements.
    /// </summary>
    Info,

    /// <summary>
    /// Indicates a verbose severity level for trace statements.
    /// </summary>
    Verbose,

    /// <summary>
    /// Indicates a debug severity level for trace statements.
    /// </summary>
    Debug,
}

/// <summary>
/// Represents a parse node for a trace statement.
/// </summary>
public class TraceStatementParseNode : StatementParseNode
{
    /// <summary>
    /// Initializes a new instance of the <see cref="TraceStatementParseNode"/> class.
    /// </summary>
    /// <param name="severity">The severity level of the trace statement.</param>
    /// <param name="expression">The expression to trace.</param>
    /// <param name="start">The starting token of the trace statement.</param>
    /// <param name="precedingComments">The comments preceding the trace statement.</param>
    public TraceStatementParseNode(
        TraceStatementSeverity severity,
        ExpressionParseNode expression,
        Token start,
        IEnumerable<CommentToken> precedingComments)
        : base(start, precedingComments)
    {
        this.Severity = severity;
        this.Expression = expression ?? throw new ArgumentNullException(nameof(expression));
    }

    /// <summary>
    /// Gets the severity level of the trace statement.
    /// </summary>
    public TraceStatementSeverity Severity { get; }

    /// <summary>
    /// Gets the expression to trace.
    /// </summary>
    public ExpressionParseNode Expression { get; }
}