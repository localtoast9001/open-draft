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
    /// Represents the message id for an invalid character error message.
    /// </summary>
    public static readonly MessageId InvalidCharacterMessageId = new MessageId(Constants.DefaultMessageCategory, 1001);

    /// <summary>
    /// Represents the message id for an unterminated multi-line comment error message.
    /// </summary>
    public static readonly MessageId UnterminatedMultiLineCommentMessageId = new MessageId(Constants.DefaultMessageCategory, 1002);

    /// <summary>
    /// Represents the message id for an unknown escape sequence error message.
    /// </summary>
    public static readonly MessageId UnknownEscapeSequenceMessageId = new MessageId(Constants.DefaultMessageCategory, 1003);

    /// <summary>
    /// Represents the message id for an invalid hexadecimal escape sequence error message.
    /// </summary>
    public static readonly MessageId InvalidHexEscapeSequenceMessageId = new MessageId(Constants.DefaultMessageCategory, 1004);

    /// <summary>
    /// Represents the message id for an unexpected end of file error message.
    /// </summary>
    public static readonly MessageId UnexpectedEndOfFileMessageId = new MessageId(Constants.DefaultMessageCategory, 2000);

    /// <summary>
    /// Represents the message id for a keyword expected error message.
    /// </summary>
    public static readonly MessageId KeywordExpectedMessageId = new MessageId(Constants.DefaultMessageCategory, 2001);

    /// <summary>
    /// Represents the message id for a symbol expected error message.
    /// </summary>
    public static readonly MessageId SymbolExpectedMessageId = new MessageId(Constants.DefaultMessageCategory, 2002);

    /// <summary>
    /// Represents the message id for an identifier expected error message.
    /// </summary>
    public static readonly MessageId IdentifierExpectedMessageId = new MessageId(Constants.DefaultMessageCategory, 2003);

    /// <summary>
    /// Represents the message id for a string literal expected error message.
    /// </summary>
    public static readonly MessageId StringLiteralExpectedMessageId = new MessageId(Constants.DefaultMessageCategory, 2004);

    /// <summary>
    /// Represents the message id for a numeric literal expected error message.
    /// </summary>
    public static readonly MessageId NumericLiteralExpectedMessageId = new MessageId(Constants.DefaultMessageCategory, 2005);

    /// <summary>
    /// Represents the message id for an integer literal expected error message.
    /// </summary>
    public static readonly MessageId IntegerLiteralExpectedMessageId = new MessageId(Constants.DefaultMessageCategory, 2006);

    /// <summary>
    /// Represents the message id for an unexpected token error message.
    /// </summary>
    public static readonly MessageId UnexpectedTokenMessageId = new MessageId(Constants.DefaultMessageCategory, 2100);

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

    /// <summary>
    /// Creates a message for an invalid character error.
    /// </summary>
    /// <param name="source">The source reference for the error.</param>
    /// <param name="character">The invalid character.</param>
    /// <returns>The created message.</returns>
    public static Message InvalidCharacter(SourceReference source, char character)
    {
        return new Message(
            MessageSeverity.Error,
            InvalidCharacterMessageId,
            source,
            $"Invalid character '{character}'.");
    }

    /// <summary>
    /// Creates a message for an unterminated multi-line comment error.
    /// </summary>
    /// <param name="source">The source reference for the error.</param>
    /// <returns>The created message.</returns>
    public static Message UnterminatedMultiLineComment(SourceReference source)
    {
        return new Message(
            MessageSeverity.Error,
            UnterminatedMultiLineCommentMessageId,
            source,
            "Unterminated multi-line comment.");
    }

    /// <summary>
    /// Creates a message for an unknown escape sequence error.
    /// </summary>
    /// <param name="source">The source reference for the error.</param>
    /// <param name="character">The unknown escape sequence character.</param>
    /// <returns>The created message.</returns>
    public static Message UnknownEscapeSequence(SourceReference source, char character)
    {
        return new Message(
            MessageSeverity.Error,
            UnknownEscapeSequenceMessageId,
            source,
            $"Unknown escape sequence '\\{character}'.");
    }

    /// <summary>
    /// Creates a message for an invalid hexadecimal escape sequence error.
    /// </summary>
    /// <param name="source">The source reference for the error.</param>
    /// <returns>The created message.</returns>
    public static Message InvalidHexEscapeSequence(SourceReference source)
    {
        return new Message(
            MessageSeverity.Error,
            InvalidHexEscapeSequenceMessageId,
            source,
            "Invalid hexadecimal escape sequence.");
    }

    /// <summary>
    /// Creates a message for an unexpected end of file error.
    /// </summary>
    /// <param name="source">The source reference for the error.</param>
    /// <returns>The created message.</returns>
    public static Message UnexpectedEndOfFile(SourceReference source)
    {
        return new Message(
            MessageSeverity.Error,
            UnexpectedEndOfFileMessageId,
            source,
            "Unexpected end of file.");
    }

    /// <summary>
    /// Creates a message for a keyword expected error.
    /// </summary>
    /// <param name="token">The token that caused the error.</param>
    /// <param name="fileSource">The source reference for the file being parsed, used if the token is null.</param>
    /// <param name="expected">The expected keyword.</param>
    /// <returns>The created message.</returns>
    public static Message KeywordExpected(
        Token? token,
        SourceReference fileSource,
        Keyword expected)
    {
        return new Message(
            MessageSeverity.Error,
            KeywordExpectedMessageId,
            token?.Source ?? fileSource,
            $"Expected keyword '{expected}', but found '{token?.ToString() ?? "end of file"}' which is not a keyword.");
    }

    /// <summary>
    /// Creates a message for a symbol expected error.
    /// </summary>
    /// <param name="token">The token that caused the error.</param>
    /// <param name="fileSource">The source reference for the file being parsed, used if the token is null.</param>
    /// <param name="expected">The expected symbol.</param>
    /// <returns>The created message.</returns>
    public static Message SymbolExpected(
        Token? token,
        SourceReference fileSource,
        Symbol expected)
    {
        return new Message(
            MessageSeverity.Error,
            SymbolExpectedMessageId,
            token?.Source ?? fileSource,
            $"Expected symbol '{expected}', but found '{token?.ToString() ?? "end of file"}' which is not a symbol.");
    }

    /// <summary>
    /// Creates a message for an identifier expected error.
    /// </summary>
    /// <param name="token">The token that caused the error.</param>
    /// <param name="fileSource">The source reference for the file being parsed, used if the token is null.</param>
    /// <returns>The created message.</returns>
    public static Message IdentifierExpected(
        Token? token,
        SourceReference fileSource)
    {
        return new Message(
            MessageSeverity.Error,
            IdentifierExpectedMessageId,
            token?.Source ?? fileSource,
            $"Expected identifier, but found '{token?.ToString() ?? "end of file"}' which is not an identifier.");
    }

    /// <summary>
    /// Creates a message for a string literal expected error.
    /// </summary>
    /// <param name="token">The token that caused the error.</param>
    /// <param name="fileSource">The source reference for the file being parsed, used if the token is null.</param>
    /// <returns>The created message.</returns>
    public static Message StringLiteralExpected(
        Token? token,
        SourceReference fileSource)
    {
        return new Message(
            MessageSeverity.Error,
            StringLiteralExpectedMessageId,
            token?.Source ?? fileSource,
            $"Expected string literal, but found '{token?.ToString() ?? "end of file"}' which is not a string literal.");
    }

    /// <summary>
    /// Creates a message for a numeric literal expected error.
    /// </summary>
    /// <param name="token">The token that caused the error.</param>
    /// <param name="fileSource">The source reference for the file being parsed, used if the token is null.</param>
    /// <returns>The created message.</returns>
    public static Message NumericLiteralExpected(
        Token? token,
        SourceReference fileSource)
    {
        return new Message(
            MessageSeverity.Error,
            NumericLiteralExpectedMessageId,
            token?.Source ?? fileSource,
            $"Expected numeric literal, but found '{token?.ToString() ?? "end of file"}' which is not a numeric literal.");
    }

    /// <summary>
    /// Creates a message for an integer literal expected error.
    /// </summary>
    /// <param name="token">The token that caused the error.</param>
    /// <param name="fileSource">The source reference for the file being parsed, used if the token is null.</param>
    /// <returns>The created message.</returns>
    public static Message IntegerLiteralExpected(
        Token? token,
        SourceReference fileSource)
    {
        return new Message(
            MessageSeverity.Error,
            IntegerLiteralExpectedMessageId,
            token?.Source ?? fileSource,
            $"Expected integer literal, but found '{token?.ToString() ?? "end of file"}' which is not an integer literal.");
    }

    /// <summary>
    /// Creates a message for an unexpected token error.
    /// </summary>
    /// <param name="token">The token that caused the error.</param>
    /// <param name="fileSource">The source reference for the file being parsed, used if the token is null.</param>
    /// <returns>The created message.</returns>
    public static Message UnexpectedToken(
        Token? token,
        SourceReference fileSource)
    {
        return new Message(
            MessageSeverity.Error,
            UnexpectedTokenMessageId,
            token?.Source ?? fileSource,
            $"Unexpected token '{token?.ToString() ?? "end of file"}'.");
    }
}