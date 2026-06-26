// <copyright file="TemplateParseNode.cs" company="Jon Rowlett">
// Copyright (c) Jon Rowlett. All rights reserved.
// </copyright>

namespace OpenDraft.Lang;

/// <summary>
/// Represents a parse node for a template declaration.
/// </summary>
public class TemplateParseNode : ProgramElementParseNode
{
    /// <summary>
    /// Initializes a new instance of the <see cref="TemplateParseNode"/> class.
    /// </summary>
    /// <param name="name">The name of the template.</param>
    /// <param name="parameters">The parameters of the template.</param>
    /// <param name="body">The body of the template.</param>
    /// <param name="start">The starting token of the template.</param>
    /// <param name="precedingComments">The comments preceding the template.</param>
    public TemplateParseNode(
        string name,
        IEnumerable<ParameterDeclarationParseNode> parameters,
        StatementParseNode body,
        Token start,
        IEnumerable<CommentToken> precedingComments)
        : base(start, precedingComments)
    {
        this.Name = name;
        this.Parameters = parameters.ToList().AsReadOnly();
        this.Body = body;
    }

    /// <summary>
    /// Gets the parameters of the template.
    /// </summary>
    public IReadOnlyList<ParameterDeclarationParseNode> Parameters { get; }

    /// <summary>
    /// Gets the body of the template.
    /// </summary>
    public StatementParseNode Body { get; }

    /// <summary>
    /// Gets the name of the template.
    /// </summary>
    public string Name { get; }
}