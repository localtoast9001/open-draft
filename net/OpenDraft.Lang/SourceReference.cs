// <copyright file="SourceReference.cs" company="Jon Rowlett">
// Copyright (c) Jon Rowlett. All rights reserved.
// </copyright>

namespace OpenDraft.Lang;

using System.Text;

/// <summary>
/// Represents a reference to a source location in the language.
/// </summary>
public class SourceReference
{
    /// <summary>
    /// Initializes a new instance of the <see cref="SourceReference"/> class.
    /// </summary>
    /// <param name="path">The path of the source file.</param>
    /// <param name="lineNumber">The line number in the source file.</param>
    /// <param name="columnNumber">The column number in the source file.</param>
    /// <param name="endLineNumber">The line number in the source file where the reference ends.</param>
    /// <param name="endColumnNumber">The column number in the source file where the reference ends.</param>
    public SourceReference(
        string path,
        int lineNumber = 0,
        int columnNumber = 0,
        int endLineNumber = 0,
        int endColumnNumber = 0)
    {
        this.Path = !string.IsNullOrEmpty(path) ?
            path :
            throw new ArgumentOutOfRangeException(nameof(path), "Path cannot be null or empty.");
        this.LineNumber = lineNumber;
        this.ColumnNumber = columnNumber;
        this.EndLineNumber = endLineNumber != 0 ? endLineNumber : lineNumber;
        this.EndColumnNumber = endColumnNumber != 0 ? endColumnNumber : columnNumber;
    }

    /// <summary>
    /// Gets the path of the source file.
    /// </summary>
    public string Path { get; }

    /// <summary>
    /// Gets the line number in the source file.
    /// </summary>
    public int LineNumber { get; }

    /// <summary>
    /// Gets the column number in the source file.
    /// </summary>
    public int ColumnNumber { get; }

    /// <summary>
    /// Gets the line number in the source file where the reference ends.
    /// </summary>
    public int EndLineNumber { get; }

    /// <summary>
    /// Gets the column number in the source file where the reference ends.
    /// </summary>
    public int EndColumnNumber { get; }

    /// <inheritdoc/>
    public override string ToString()
    {
        StringBuilder sb = new StringBuilder();
        sb.Append(this.Path);
        if (this.LineNumber > 0)
        {
            sb.Append($"({this.LineNumber}");
            if (this.ColumnNumber > 0)
            {
                sb.Append($",{this.ColumnNumber}");
            }

            if (this.EndLineNumber != this.LineNumber || this.EndColumnNumber != this.ColumnNumber)
            {
                sb.Append($",{this.EndLineNumber}");
                if (this.EndColumnNumber > 0)
                {
                    sb.Append($",{this.EndColumnNumber}");
                }
            }

            sb.Append(")");
        }

        return sb.ToString();
    }
}