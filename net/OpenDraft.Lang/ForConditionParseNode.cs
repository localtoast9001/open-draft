// <copyright file="ForConditionParseNode.cs" company="Jon Rowlett">
// Copyright (c) Jon Rowlett. All rights reserved.
// </copyright>

namespace OpenDraft.Lang;

/// <summary>
/// Represents a condition in a for loop.
/// </summary>
public class ForConditionParseNode : ParseNode
{
    /// <summary>
    /// Initializes a new instance of the <see cref="ForConditionParseNode"/> class.
    /// </summary>
    /// <param name="variableNames">The variable names declared in the for loop condition.</param>
    /// <param name="expression">The expression representing the for loop condition.</param>
    /// <param name="typeReference">The type reference of the variables declared in the for loop condition.</param>
    /// <param name="start">The starting token of the for loop condition.</param>
    /// <param name="precedingComments">The comments preceding the for loop condition.</param>
    public ForConditionParseNode(
        IEnumerable<string> variableNames,
        ExpressionParseNode expression,
        TypeReferenceParseNode? typeReference,
        Token start,
        IEnumerable<CommentToken> precedingComments)
        : base(start, precedingComments)
    {
        this.VariableNames = variableNames.ToList().AsReadOnly();
        this.TypeReference = typeReference;
        this.Expression = expression ?? throw new ArgumentNullException(nameof(expression));
    }

    /// <summary>
    /// Gets the variable names declared in the for loop condition.
    /// </summary>
    public IReadOnlyList<string> VariableNames { get; }

    /// <summary>
    /// Gets the type reference of the variables declared in the for loop condition.
    /// </summary>
    public TypeReferenceParseNode? TypeReference { get; }

    /// <summary>
    /// Gets the expression representing the for loop condition.
    /// </summary>
    public ExpressionParseNode Expression { get; }
}