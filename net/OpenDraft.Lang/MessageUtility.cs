// <copyright file="MessageUtility.cs" company="Jon Rowlett">
// Copyright (c) Jon Rowlett. All rights reserved.
// </copyright>

namespace OpenDraft.Lang;

/// <summary>
/// Helpers for creating messages produced by the language components.
/// </summary>
internal static class MessageUtility
{
    /// <summary>
    /// Represents the message id for an unterminated string literal error message.
    /// </summary>
    public static readonly MessageId UnterminatedStringLiteralMessageId = new MessageId(Constants.DefaultMessageCategory, 1000);

    /// <summary>
    /// Creates a message for an unterminated string literal error.
    /// </summary>
    /// <param name="source">The source reference for the error.</param>
    /// <returns>The created message.</returns>
    public static Message UnterminatedStringLiteral(SourceReference source)
    {
        return new Message(
            MessageSeverity.Error,
            UnterminatedStringLiteralMessageId,
            source,
            "Unterminated string literal.");
    }
}