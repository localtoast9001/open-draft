// <copyright file="TemplateDeclarationParseNode.cs" company="Jon Rowlett">
// Copyright (c) Jon Rowlett. All rights reserved.
// </copyright>

namespace OpenDraft.Lang;

/// <summary>
/// Declares a template member in an interface in the language.
/// </summary>
public class TemplateDeclarationParseNode : InterfaceMemberParseNode
{
    /// <summary>
    /// Initializes a new instance of the <see cref="TemplateDeclarationParseNode"/> class.
    /// </summary>
    /// <param name="name">The name of the template.</param>
    /// <param name="parameters">The parameters of the template.</param>
    /// <param name="start">The starting token of the template declaration.</param>
    /// <param name="precedingComments">The comments preceding the template declaration.</param>
    public TemplateDeclarationParseNode(
        string name,
        IEnumerable<ParameterDeclarationParseNode> parameters,
        Token start,
        IEnumerable<CommentToken> precedingComments)
        : base(name, start, precedingComments)
    {
        this.Parameters = parameters.ToList().AsReadOnly();
    }

    /// <summary>
    /// Gets the parameters of the template.
    /// </summary>
    public IReadOnlyList<ParameterDeclarationParseNode> Parameters { get; }
}