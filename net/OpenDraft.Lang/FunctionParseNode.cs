// <copyright file="FunctionParseNode.cs" company="Jon Rowlett">
// Copyright (c) Jon Rowlett. All rights reserved.
// </copyright>
namespace OpenDraft.Lang;

/// <summary>
/// Represents a parse node for a function declaration.
/// </summary>
public class FunctionParseNode : ProgramElementParseNode
{
    /// <summary>
    /// Initializes a new instance of the <see cref="FunctionParseNode"/> class.
    /// </summary>
    /// <param name="name">The name of the function.</param>
    /// <param name="parameters">The parameters of the function.</param>
    /// <param name="body">The body of the function.</param>
    /// <param name="start">The starting token of the function.</param>
    /// <param name="precedingComments">The comments preceding the function.</param>
    public FunctionParseNode(
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
    /// Gets the name of the function.
    /// </summary>
    public string Name { get; }

    /// <summary>
    /// Gets the parameters of the function.
    /// </summary>
    public IReadOnlyList<ParameterDeclarationParseNode> Parameters { get; }

    /// <summary>
    /// Gets the body of the function.
    /// </summary>
    public StatementParseNode Body { get; }
}