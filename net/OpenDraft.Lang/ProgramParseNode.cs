// <copyright file="ProgramParseNode.cs" company="Jon Rowlett">
// Copyright (c) Jon Rowlett. All rights reserved.
// </copyright>

namespace OpenDraft.Lang;

/// <summary>
/// Represents the root node of the parse tree for a program. This node is created when the parser successfully parses an entire program. It contains the list of top-level declarations in the program, such as import statements, class declarations, interface declarations, and enum declarations. This node also contains the token that starts the program and any comments that precede it, which are stored in the base <see cref="ParseNode"/> class.
/// </summary>
public class ProgramParseNode : ParseNode
{
    /// <summary>
    /// Initializes a new instance of the <see cref="ProgramParseNode"/> class with the specified list of import statements, starting token, and preceding comments.
    /// </summary>
    /// <param name="imports">The list of import statements in the program.</param>
    /// <param name="programElements">The list of program elements in the program.</param>
    /// <param name="start">The token that starts the program.</param>
    /// <param name="precedingComments">The comments that precede the program.</param>
    /// <exception cref="ArgumentNullException">Thrown when <paramref name="imports"/> is <c>null</c>.</exception>
    public ProgramParseNode(
        IEnumerable<ImportParseNode> imports,
        IEnumerable<ProgramElementParseNode> programElements,
        Token start,
        IEnumerable<CommentToken> precedingComments)
        : base(start, precedingComments)
    {
        this.Imports = imports?.ToList() ?? throw new ArgumentNullException(nameof(imports));
        this.ProgramElements = programElements?.ToList() ?? throw new ArgumentNullException(nameof(programElements));
    }

    /// <summary>
    /// Gets the list of import statements in the program. This list is populated by the parser as it encounters import statements in the source code. Each import statement is represented as an <see cref="ImportParseNode"/> object, which contains the module name being imported and the token that starts the import statement.
    /// </summary>
    public IReadOnlyList<ImportParseNode> Imports { get; }

    /// <summary>
    /// Gets the list of program elements in the program. This list is populated by the parser as it encounters program elements in the source code. Each program element is represented as a <see cref="ProgramElementParseNode"/> object, which contains the details of the program element and the token that starts it.
    /// </summary>
    public IReadOnlyList<ProgramElementParseNode> ProgramElements { get; }
}