// <copyright file="ParameterDeclarationParseNode.cs" company="Jon Rowlett">
// Copyright (c) Jon Rowlett. All rights reserved.
// </copyright>

namespace OpenDraft.Lang;

/// <summary>
/// Represents a parameter declaration in the language.
/// </summary>
public class ParameterDeclarationParseNode : ParseNode
{
    /// <summary>
    /// Initializes a new instance of the <see cref="ParameterDeclarationParseNode"/> class.
    /// </summary>
    /// <param name="name">The name of the parameter.</param>
    /// <param name="type">The type of the parameter.</param>
    /// <param name="defaultValue">The default value of the parameter, or null if no default value was specified.</param>
    /// <param name="start">The starting token of the parameter declaration.</param>
    /// <param name="precedingComments">The comments preceding the parameter declaration.</param>
    /// <exception cref="ArgumentNullException">Thrown if <paramref name="name"/> is null.</exception>
    public ParameterDeclarationParseNode(
        string name,
        TypeReferenceParseNode? type,
        ExpressionParseNode? defaultValue,
        Token start,
        IEnumerable<CommentToken> precedingComments)
        : base(start, precedingComments)
    {
        this.Name = name ?? throw new ArgumentNullException(nameof(name));
        this.Type = type;
        this.DefaultValue = defaultValue;
    }

    /// <summary>
    /// Gets the name of the parameter.
    /// </summary>
    public string Name { get; }

    /// <summary>
    /// Gets the type of the parameter.
    /// </summary>
    public TypeReferenceParseNode? Type { get; }

    /// <summary>
    /// Gets the default value of the parameter, or null if no default value was specified. If a default value was specified, this expression will be evaluated at compile time and the resulting value will be used as the default value for the parameter when it is not provided by the caller. If no default value was specified, then the parameter is required and must be provided by the caller. Note that parameters with default values must come after all required parameters in the parameter list; this is enforced by the parser and will result in a syntax error if violated.
    /// </summary>
    public ExpressionParseNode? DefaultValue { get; }
}