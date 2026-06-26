// <copyright file="FunctionDeclarationParseNode.cs" company="Jon Rowlett">
// Copyright (c) Jon Rowlett. All rights reserved.
// </copyright>

namespace OpenDraft.Lang;

/// <summary>
/// Declares a function member in an interface in the language.
/// </summary>
public class FunctionDeclarationParseNode : InterfaceMemberParseNode
{
    /// <summary>
    /// Initializes a new instance of the <see cref="FunctionDeclarationParseNode"/> class.
    /// </summary>
    /// <param name="start">The starting token of the function declaration.</param>
    /// <param name="precedingComments">The comments preceding the function declaration.</param>
    /// <param name="name">The name of the function.</param>
    /// <param name="parameters">The parameters of the function.</param>
    public FunctionDeclarationParseNode(
        string name,
        IEnumerable<ParameterDeclarationParseNode> parameters,
        Token start,
        IEnumerable<CommentToken> precedingComments)
        : base(start, precedingComments)
    {
        this.Name = name;
        this.Parameters = parameters.ToList().AsReadOnly();
    }

    /// <summary>
    /// Gets the name of the function.
    /// </summary>
    public string Name { get; }

    /// <summary>
    /// Gets the parameters of the function.
    /// </summary>
    public IReadOnlyList<ParameterDeclarationParseNode> Parameters { get; }
}