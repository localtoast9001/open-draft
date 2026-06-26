// <copyright file="ImportParseNode.cs" company="Jon Rowlett">
// Copyright (c) Jon Rowlett. All rights reserved.
// </copyright>

namespace OpenDraft.Lang;

/// <summary>
/// Represents an import statement in the parse tree. This node is created when the parser encounters an 'import' keyword followed by a module name. The module name is stored in the <see cref="ModuleName"/> property. This node also contains the token that starts the import statement and any comments that precede it, which are stored in the base <see cref="ParseNode"/> class.
/// </summary>
public class ImportParseNode : ParseNode
{
    /// <summary>
    /// Initializes a new instance of the <see cref="ImportParseNode"/> class with the specified module name, starting token, and preceding comments.
    /// </summary>
    /// <param name="moduleName">The name of the module being imported.</param>
    /// <param name="start">The token that starts the import statement.</param>
    /// <param name="precedingComments">The comments that precede the import statement.</param>
    /// <exception cref="ArgumentNullException">Thrown when <paramref name="moduleName"/> is <c>null</c>.</exception>
    public ImportParseNode(
        string moduleName,
        Token start,
        IEnumerable<CommentToken> precedingComments)
        : base(start, precedingComments)
    {
        this.ModuleName = moduleName ?? throw new ArgumentNullException(nameof(moduleName));
    }

    /// <summary>
    /// Gets the name of the module being imported.
    /// </summary>
    public string ModuleName { get; }
}