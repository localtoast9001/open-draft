// <copyright file="KeywordTokenTests.cs" company="Jon Rowlett">
// Copyright (c) Jon Rowlett. All rights reserved.
// </copyright>

namespace OpenDraft.Lang.UnitTest;

/// <summary>
/// Unit tests for the <see cref="KeywordToken"/> class.
/// </summary>
[TestClass]
public class KeywordTokenTests
{
    /// <summary>
    /// Tests that a <see cref="KeywordToken"/> can be created with a valid source and keyword value.
    /// </summary>
    [TestMethod]
    public void Constructor_WithValidSourceAndValue_CreatesInstance()
    {
        // Arrange
        var source = new SourceReference("test.odl", 1, 2);
        var value = Keyword.Class;

        // Act
        var token = new KeywordToken(source, value);

        // Assert
        Assert.AreSame(source, token.Source);
        Assert.AreEqual(value, token.Value);
    }

    /// <summary>
    /// Tests that constructor throws when source is null.
    /// </summary>
    [TestMethod]
    public void Constructor_WithNullSource_ThrowsException()
    {
        try
        {
            // Act
            _ = new KeywordToken(null!, Keyword.Class);
            Assert.Fail("Expected ArgumentNullException for null source.");
        }
        catch (ArgumentNullException ex)
        {
            // Assert
            Assert.AreEqual("source", ex.ParamName);
        }
    }

    /// <summary>
    /// Tests that constructor throws when value is Keyword.None.
    /// </summary>
    [TestMethod]
    public void Constructor_WithNoneValue_ThrowsException()
    {
        try
        {
            // Arrange
            var source = new SourceReference("test.odl");

            // Act
            _ = new KeywordToken(source, Keyword.None);
            Assert.Fail("Expected ArgumentOutOfRangeException for Keyword.None.");
        }
        catch (ArgumentOutOfRangeException ex)
        {
            // Assert
            Assert.AreEqual("value", ex.ParamName);
            StringAssert.Contains(ex.Message, "Value cannot be None.");
        }
    }

    /// <summary>
    /// Tests that ToString() returns the keyword text representation.
    /// </summary>
    [TestMethod]
    public void ToString_WithValidValue_ReturnsKeywordText()
    {
        // Arrange
        var source = new SourceReference("test.odl");
        var token = new KeywordToken(source, Keyword.Interface);

        // Act
        var result = token.ToString();

        // Assert
        Assert.AreEqual("interface", result);
    }

    /// <summary>
    /// Tests that different keyword values return expected text.
    /// </summary>
    [TestMethod]
    public void ToString_WithDifferentKeywords_ReturnsExpectedText()
    {
        // Arrange
        var source = new SourceReference("test.odl");

        // Act and Assert
        Assert.AreEqual("class", new KeywordToken(source, Keyword.Class).ToString());
        Assert.AreEqual("enum", new KeywordToken(source, Keyword.Enum).ToString());
        Assert.AreEqual("if", new KeywordToken(source, Keyword.If).ToString());
        Assert.AreEqual("for", new KeywordToken(source, Keyword.For).ToString());
    }
}
