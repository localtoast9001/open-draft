// <copyright file="VariableDefinitionParseNode.cs" company="Jon Rowlett">
// Copyright (c) Jon Rowlett. All rights reserved.
// </copyright>

namespace OpenDraft.Lang;

/// <summary>
/// Represents a variable definition in the language.
/// </summary>
public class VariableDefinitionParseNode : StatementParseNode
{
    /// <summary>
    /// Initializes a new instance of the <see cref="VariableDefinitionParseNode"/> class.
    /// </summary>
    /// <param name="name">The name of the variable being defined.</param>
    /// <param name="type">The type of the variable being defined, or null if no type was specified.</param>
    /// <param name="value">The expression that represents the value being assigned to the variable.</param>
    /// <param name="start">The starting token of the variable definition.</param>
    /// <param name="precedingComments">The comments preceding the variable definition.</param>
    public VariableDefinitionParseNode(
        string name,
        TypeReferenceParseNode? type,
        ExpressionParseNode value,
        Token start,
        IEnumerable<CommentToken> precedingComments)
        : base(start, precedingComments)
    {
        this.Name = name ?? throw new ArgumentNullException(nameof(name));
        this.Type = type;
        this.Value = value ?? throw new ArgumentNullException(nameof(value));
    }

    /// <summary>
    /// Gets the name of the variable being defined.
    /// </summary>
    public string Name { get; }

    /// <summary>
    /// Gets the type of the variable being defined, or null if no type was specified (i.e., if the type should be inferred from the value).
    /// </summary>
    public TypeReferenceParseNode? Type { get; }

    /// <summary>
    /// Gets the expression that represents the value being assigned to the variable. This is required, as variable definitions must have an initializer in this language.
    /// </summary>
    public ExpressionParseNode Value { get; }
}