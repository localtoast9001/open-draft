// <copyright file="TokenReaderTests.cs" company="Jon Rowlett">
// Copyright (c) Jon Rowlett. All rights reserved.
// </copyright>

namespace OpenDraft.Lang.UnitTest;

using System.IO;

/// <summary>
/// Basic unit tests for the <see cref="TokenReader"/> class.
/// </summary>
[TestClass]
public class TokenReaderTests
{
    /// <summary>
    /// Tests that constructor throws when inner reader is null.
    /// </summary>
    [TestMethod]
    public void Constructor_WithNullInner_ThrowsException()
    {
        try
        {
            // Arrange
            var startSource = new SourceReference("test.odl");

            // Act
            _ = new TokenReader(null!, startSource, _ => { });
            Assert.Fail("Expected ArgumentNullException for null inner reader.");
        }
        catch (ArgumentNullException ex)
        {
            // Assert
            Assert.AreEqual("inner", ex.ParamName);
        }
    }

    /// <summary>
    /// Tests that constructor throws when start source is null.
    /// </summary>
    [TestMethod]
    public void Constructor_WithNullStartSource_ThrowsException()
    {
        try
        {
            // Arrange
            using var inner = new StringReader("x");

            // Act
            _ = new TokenReader(inner, null!, _ => { });
            Assert.Fail("Expected ArgumentNullException for null start source.");
        }
        catch (ArgumentNullException ex)
        {
            // Assert
            Assert.AreEqual("startSource", ex.ParamName);
        }
    }

    /// <summary>
    /// Tests that constructor throws when log callback is null.
    /// </summary>
    [TestMethod]
    public void Constructor_WithNullLog_ThrowsException()
    {
        try
        {
            // Arrange
            using var inner = new StringReader("x");
            var startSource = new SourceReference("test.odl");

            // Act
            _ = new TokenReader(inner, startSource, null!);
            Assert.Fail("Expected ArgumentNullException for null log callback.");
        }
        catch (ArgumentNullException ex)
        {
            // Assert
            Assert.AreEqual("log", ex.ParamName);
        }
    }

    /// <summary>
    /// Tests that Read() returns null for empty input.
    /// </summary>
    [TestMethod]
    public void Read_WithEmptyInput_ReturnsNull()
    {
        // Arrange
        using var reader = new TokenReader(
            new StringReader(string.Empty),
            new SourceReference("test.odl"),
            _ => { });

        // Act
        var token = reader.Read();

        // Assert
        Assert.IsNull(token);
    }

    /// <summary>
    /// Tests that Peek() does not consume token and Read() returns the same token instance.
    /// </summary>
    [TestMethod]
    public void Peek_ThenRead_ReturnsSameTokenInstance()
    {
        // Arrange
        using var reader = new TokenReader(
            new StringReader("+"),
            new SourceReference("test.odl"),
            _ => { });

        // Act
        var peeked = reader.Peek();
        var read = reader.Read();
        var end = reader.Read();

        // Assert
        Assert.IsNotNull(peeked);
        Assert.IsInstanceOfType<SymbolToken>(peeked);
        Assert.AreSame(peeked, read);
        Assert.IsNull(end);
        var symbol = (SymbolToken)read!;
        Assert.AreEqual(Symbol.Plus, symbol.Value);
    }

    /// <summary>
    /// Tests that identifier text is returned as <see cref="IdentifierToken"/>.
    /// </summary>
    [TestMethod]
    public void Read_WithIdentifier_ReturnsIdentifierToken()
    {
        // Arrange
        using var reader = new TokenReader(
            new StringReader("alpha_1"),
            new SourceReference("test.odl"),
            _ => { });

        // Act
        var token = reader.Read();

        // Assert
        Assert.IsNotNull(token);
        Assert.IsInstanceOfType<IdentifierToken>(token);
        var identifier = (IdentifierToken)token;
        Assert.AreEqual("alpha_1", identifier.Value);
        Assert.AreEqual("test.odl", identifier.Source.Path);
    }

    /// <summary>
    /// Tests that keyword text is returned as <see cref="KeywordToken"/>.
    /// </summary>
    [TestMethod]
    public void Read_WithKeyword_ReturnsKeywordToken()
    {
        // Arrange
        using var reader = new TokenReader(
            new StringReader("class"),
            new SourceReference("test.odl"),
            _ => { });

        // Act
        var token = reader.Read();

        // Assert
        Assert.IsNotNull(token);
        Assert.IsInstanceOfType<KeywordToken>(token);
        var keyword = (KeywordToken)token;
        Assert.AreEqual(Keyword.Class, keyword.Value);
    }

    /// <summary>
    /// Tests that a sequence of symbols delimited by a specific character is read correctly.
    /// </summary>
    [TestMethod]
    public void ReadSymbolDelimitedSequence()
    {
        TestMessageLog log = new TestMessageLog();
        var target = CreateReader(log, "a = 1; return b + 5;");
        List<Token> actual = new();
        Token? token;
        while ((token = target.Read()) != null)
        {
            actual.Add(token);
        }

        // Assert
        Assert.HasCount(9, actual);
        Assert.IsInstanceOfType(actual[0], typeof(IdentifierToken));
        Assert.IsInstanceOfType(actual[1], typeof(SymbolToken));
        Assert.IsInstanceOfType(actual[2], typeof(NumericLiteralToken));
        Assert.IsInstanceOfType(actual[3], typeof(SymbolToken));
        Assert.IsInstanceOfType(actual[4], typeof(KeywordToken));
        Assert.IsInstanceOfType(actual[5], typeof(IdentifierToken));
        Assert.IsInstanceOfType(actual[6], typeof(SymbolToken));
        Assert.IsInstanceOfType(actual[7], typeof(NumericLiteralToken));
        Assert.IsInstanceOfType(actual[8], typeof(SymbolToken));
    }

    private static TokenReader CreateReader(TestMessageLog log, string text)
    {
        return new TokenReader(
            new StringReader(text),
            new SourceReference("test.odl"),
            log.Log);
    }
}
