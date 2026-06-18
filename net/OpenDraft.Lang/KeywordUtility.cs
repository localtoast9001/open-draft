// <copyright file="KeywordUtility.cs" company="Jon Rowlett">
// Copyright (c) Jon Rowlett. All rights reserved.
// </copyright>

namespace OpenDraft.Lang;

/// <summary>
/// Helper methods for working with <see cref="Keyword"/> values.
/// </summary>
internal static class KeywordUtility
{
    /// <summary>
    /// Gets the <see cref="Keyword"/> value for the specified text.
    /// </summary>
    /// <param name="text">The text to get the keyword for.</param>
    /// <returns>The corresponding <see cref="Keyword"/> value, or <see cref="Keyword.None"/> if the text is not a keyword.</returns>
    public static Keyword GetKeyword(string text)
    {
        return text switch
        {
            "class" => Keyword.Class,
            "interface" => Keyword.Interface,
            "enum" => Keyword.Enum,
            "if" => Keyword.If,
            "for" => Keyword.For,
            _ => Keyword.None,
        };
    }

    /// <summary>
    /// Gets the text representation of the specified <see cref="Keyword"/> value.
    /// </summary>
    /// <param name="keyword">The keyword value to get the text for.</param>
    /// <returns>The text representation of the keyword.</returns>
    /// <exception cref="ArgumentOutOfRangeException">Thrown if the keyword value is invalid.</exception>
    public static string GetText(Keyword keyword)
    {
        return keyword switch
        {
            Keyword.Class => "class",
            Keyword.Interface => "interface",
            Keyword.Enum => "enum",
            Keyword.If => "if",
            Keyword.For => "for",
            _ => throw new ArgumentOutOfRangeException(nameof(keyword), "Invalid keyword value."),
        };
    }
}