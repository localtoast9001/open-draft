// <copyright file="TokenReaderStringLiteralTests.cs" company="Jon Rowlett">
// Copyright (c) Jon Rowlett. All rights reserved.
// </copyright>

namespace OpenDraft.Lang.UnitTest;

using System.IO;
using System.Runtime.CompilerServices;

/// <summary>
/// Unit tests for the <see cref="TokenReader"/> class, specifically focusing on string literal parsing.
/// </summary>
[TestClass]
public class TokenReaderStringLiteralTests
{
    /// <summary>
    /// Tests the parsing of an empty string literal.
    /// </summary>
    [TestMethod]
    public void EmptyStringTest()
    {
        SingleTokenCleanTest(
            expectedValue: string.Empty,
            input: "\"\"");
    }

    /// <summary>
    /// Tests the parsing of a basic string literal.
    /// </summary>
    [TestMethod]
    public void BasicStringTest()
    {
        SingleTokenCleanTest(
            expectedValue: "Hello, World!",
            input: "\"Hello, World!\"");
    }

    /// <summary>
    /// Tests the parsing of a string literal containing escape sequences.
    /// </summary>
    [TestMethod]
    public void EscapedStringTest()
    {
        SingleTokenCleanTest(
            expectedValue: "Hello, \"World\"!",
            input: "\"Hello, \\\"World\\\"!\"");
    }

    /// <summary>
    /// Tests the parsing of a string literal containing an emoji.
    /// </summary>
    [TestMethod]
    public void EmojiStringTest()
    {
        SingleTokenCleanTest(
            expectedValue: "Hello, 🌍!",
            input: "\"Hello, 🌍!\"");
    }

    /// <summary>
    /// Tests the parsing of a string literal containing Hebrew characters.
    /// </summary>
    [TestMethod]
    public void HebrewStringTest()
    {
        SingleTokenCleanTest(
            expectedValue: "שלום עולם",
            input: "\"שלום עולם\"");
    }

    /// <summary>
    /// Tests the parsing of a string literal containing Arabic characters.
    /// </summary>
    [TestMethod]
    public void ArabicStringTest()
    {
        SingleTokenCleanTest(
            expectedValue: "مرحبا بالعالم",
            input: "\"مرحبا بالعالم\"");
    }

    /// <summary>
    /// Tests the parsing of a string literal containing Traditional Chinese characters.
    /// </summary>
    [TestMethod]
    public void TraditionalChineseStringTest()
    {
        SingleTokenCleanTest(
            expectedValue: "屙屎屙飯",
            input: "\"屙屎屙飯\"");
    }

    /// <summary>
    /// Tests the parsing of a string literal containing Simplified Chinese characters.
    /// </summary>
    [TestMethod]
    public void SimplifiedChineseStringTest()
    {
        SingleTokenCleanTest(
            expectedValue: "吃屎",
            input: "\"吃屎\"");
    }

    /// <summary>
    /// Tests the parsing of a string literal containing Japanese characters.
    /// </summary>
    [TestMethod]
    public void JapaneseStringTest()
    {
        SingleTokenCleanTest(
            expectedValue: "うんこを食べる",
            input: "\"うんこを食べる\"");
    }

    /// <summary>
    /// Tests the parsing of a string literal containing Korean characters.
    /// </summary>
    [TestMethod]
    public void KoreanStringTest()
    {
        SingleTokenCleanTest(
            expectedValue: "똥을 먹다",
            input: "\"똥을 먹다\"");
    }

    /// <summary>
    /// Tests the parsing of a string literal containing escape sequences.
    /// </summary>
    [TestMethod]
    public void EscapeSequenceTest()
    {
        SingleTokenCleanTest(
            expectedValue: "Hello, \"World\"!\nNew line.",
            input: "\"Hello, \\\"World\\\"!\\nNew line.\"");
    }

    /// <summary>
    /// Tests the parsing of a string literal containing all escape sequences.
    /// </summary>
    [TestMethod]
    public void AllEscapeSequenceTest()
    {
        SingleTokenCleanTest(
            expectedValue: "\a\b\f\n\r\t\v\\\"",
            input: "\"\\a\\b\\f\\n\\r\\t\\v\\\\\\\"\"");
    }

    /// <summary>
    /// Tests the parsing of a string literal containing hexadecimal escape sequences.
    /// </summary>
    [TestMethod]
    public void HexadecimalEscapeSequenceTest()
    {
        SingleTokenCleanTest(
            expectedValue: "Hello, World! \x41\x42\x43",
            input: "\"Hello, World! \\x41\\x42\\x43\"");
    }

    /// <summary>
    /// Tests the parsing of a string literal containing UTF-8 hexadecimal escape sequences.
    /// </summary>
    [TestMethod]
    public void Utf8HexEscapeSequenceTest()
    {
        SingleTokenCleanTest(
            expectedValue: "🤡🌎",
            input: "\"\\xF0\\x9F\\xA4\\xA1\\xF0\\x9F\\x8C\\x8E\"");
    }

    /// <summary>
    /// Tests the parsing of a string literal containing a single-digit hexadecimal escape sequence.
    /// </summary>
    [TestMethod]
    public void SingleDigitHexEscapeSequenceTest()
    {
        SingleTokenCleanTest(
            expectedValue: "Hello, World! \xA",
            input: "\"Hello, World! \\xA\"");
    }

    /// <summary>
    /// Tests the parsing of a string literal containing an embedded null character.
    /// </summary>
    [TestMethod]
    public void EmbeddedNullCharacterTest()
    {
        SingleTokenCleanTest(
            expectedValue: "Hello, World! \0",
            input: "\"Hello, World! \\x00\"");
    }

    /// <summary>
    /// Tests the parsing of a string literal containing a mixed-case hexadecimal escape sequence.
    /// </summary>
    [TestMethod]
    public void MixedCaseHexEscapeSequenceTest()
    {
        SingleTokenCleanTest(
            expectedValue: "Hello, World! \x0A\x0A\x0A\x0A",
            input: "\"Hello, World! \\xA\\xa\\x0a\\x0A\"");
    }

    /// <summary>
    /// Tests that unterminated string literal logs an error message and returns null.
    /// </summary>
    [TestMethod]
    public void Read_WithUnterminatedString_LogsMessageAndReturnsNull()
    {
        // Arrange
        Message? logged = null;
        using var reader = new TokenReader(
            new StringReader("\"unterminated"),
            new SourceReference("test.odl"),
            message => logged = message);

        // Act
        var token = reader.Read();

        // Assert
        Assert.IsNull(token);
        Assert.IsNotNull(logged);
        Assert.AreEqual(MessageSeverity.Error, logged.Severity);
        Assert.AreEqual(MessageUtility.UnterminatedStringLiteralMessageId, logged.Id);
        Assert.AreEqual("Unterminated string literal.", logged.Text);
    }

    /// <summary>
    /// Tests that a string literal containing a newline character logs an error message and returns null.
    /// </summary>
    [TestMethod]
    public void Read_WithNewlineInString_LogsMessageAndReturnsNull()
    {
        // Arrange
        Message? logged = null;
        using var reader = new TokenReader(
            new StringReader("\"unterminated\n"),
            new SourceReference("test.odl"),
            message => logged = message);

        // Act
        var token = reader.Read();

        // Assert
        Assert.IsNull(token);
        Assert.IsNotNull(logged);
        Assert.AreEqual(MessageSeverity.Error, logged.Severity);
        Assert.AreEqual(MessageUtility.UnterminatedStringLiteralMessageId, logged.Id);
        Assert.AreEqual("Unterminated string literal.", logged.Text);
    }

    /// <summary>
    /// Tests that a string literal containing an invalid escape sequence logs an error message and returns null.
    /// </summary>
    [TestMethod]
    public void Read_InvalidEscapeSequence_LogsMessageAndReturnsNull()
    {
        // Arrange
        Message? logged = null;
        using var reader = new TokenReader(
            new StringReader("\"invalid\\escape\""),
            new SourceReference("test.odl"),
            message => logged = message);

        // Act
        var token = reader.Read();

        // Assert
        Assert.IsNull(token);
        Assert.IsNotNull(logged);
        Assert.AreEqual(MessageSeverity.Error, logged.Severity);
        Assert.AreEqual(MessageUtility.UnknownEscapeSequenceMessageId, logged.Id);
        Assert.AreEqual("Unknown escape sequence '\\e'.", logged.Text);
    }

    /// <summary>
    /// Tests that a string literal containing an invalid hexadecimal escape sequence logs an error message and returns null.
    /// </summary>
    [TestMethod]
    public void Read_InvalidHexEscapeSequence_LogsMessageAndReturnsNull()
    {
        // Arrange
        Message? logged = null;
        using var reader = new TokenReader(
            new StringReader("\"invalid\\xG\""),
            new SourceReference("test.odl"),
            message => logged = message);

        // Act
        var token = reader.Read();

        // Assert
        Assert.IsNull(token);
        Assert.IsNotNull(logged);
        Assert.AreEqual(MessageSeverity.Error, logged.Severity);
        Assert.AreEqual(MessageUtility.InvalidHexEscapeSequenceMessageId, logged.Id);
        Assert.AreEqual("Invalid hexadecimal escape sequence.", logged.Text);
    }

    /// <summary>
    /// Tests that a string literal containing an incomplete hexadecimal escape sequence logs an error message and returns null.
    /// </summary>
    [TestMethod]
    public void Read_EndOfStringInHexEscapeSequence_LogsMessageAndReturnsNull()
    {
        // Arrange
        Message? logged = null;
        using var reader = new TokenReader(
            new StringReader("\"unterminated\\x\""),
            new SourceReference("test.odl"),
            message => logged = message);

        // Act
        var token = reader.Read();

        // Assert
        Assert.IsNull(token);
        Assert.IsNotNull(logged);
        Assert.AreEqual(MessageSeverity.Error, logged.Severity);
        Assert.AreEqual(MessageUtility.InvalidHexEscapeSequenceMessageId, logged.Id);
        Assert.AreEqual("Invalid hexadecimal escape sequence.", logged.Text);
    }

    private static TokenReader CreateTokenReader(
        string input,
        TestMessageLog log,
        [CallerFilePath] string filePath = "",
        [CallerLineNumber] int lineNumber = 0)
    {
        return new TokenReader(
            new StringReader(input),
            new SourceReference(filePath, lineNumber),
            log.Log);
    }

    private static void SingleTokenCleanTest(
        string expectedValue,
        string input)
    {
        var log = new TestMessageLog();

        TokenReader reader = CreateTokenReader(input, log);
        var token = reader.Read();
        Assert.IsNotNull(token);
        Assert.IsInstanceOfType<StringLiteralToken>(token);
        Assert.AreEqual(expectedValue, ((StringLiteralToken)token).Value);

        Assert.IsNull(reader.Read());
        log.AssertClean();
    }
}