// <copyright file="VariableReferenceParseNode.cs" company="Jon Rowlett">
// Copyright (c) Jon Rowlett. All rights reserved.
// </copyright>

namespace OpenDraft.Lang;

/// <summary>
/// Represents a variable reference expression in the language.
/// </summary>
public class VariableReferenceParseNode : ReferenceExpressionParseNode
{
    /// <summary>
    /// Initializes a new instance of the <see cref="VariableReferenceParseNode"/> class.
    /// </summary>
    /// <param name="name">The name of the variable being referenced.</param>
    /// <param name="start">The starting token of the variable reference.</param>
    /// <param name="precedingComments">The comments preceding the variable reference.</param>
    public VariableReferenceParseNode(
        string name,
        Token start,
        IEnumerable<CommentToken> precedingComments)
        : base(start, precedingComments)
    {
        this.Name = name ?? throw new ArgumentNullException(nameof(name));
    }

    /// <summary>
    /// Gets the name of the variable being referenced.
    /// </summary>
    public string Name { get; }
}