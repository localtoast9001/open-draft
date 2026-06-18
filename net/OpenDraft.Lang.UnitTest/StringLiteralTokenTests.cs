// <copyright file="StringLiteralTokenTests.cs" company="Jon Rowlett">
// Copyright (c) Jon Rowlett. All rights reserved.
// </copyright>

namespace OpenDraft.Lang.UnitTest;

/// <summary>
/// Unit tests for the <see cref="StringLiteralToken"/> class.
/// </summary>
[TestClass]
public class StringLiteralTokenTests
{
    /// <summary>
    /// Tests that a <see cref="StringLiteralToken"/> can be created with valid source and value.
    /// </summary>
    [TestMethod]
    public void Constructor_WithValidSourceAndValue_CreatesInstance()
    {
        // Arrange
        var source = new SourceReference("test.odl", 1, 2);
        var value = "hello";

        // Act
        var token = new StringLiteralToken(source, value);

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
            _ = new StringLiteralToken(null!, "hello");
            Assert.Fail("Expected ArgumentNullException for null source.");
        }
        catch (ArgumentNullException ex)
        {
            // Assert
            Assert.AreEqual("source", ex.ParamName);
        }
    }

    /// <summary>
    /// Tests that constructor throws when value is null.
    /// </summary>
    [TestMethod]
    public void Constructor_WithNullValue_ThrowsException()
    {
        try
        {
            // Arrange
            var source = new SourceReference("test.odl");

            // Act
            _ = new StringLiteralToken(source, null!);
            Assert.Fail("Expected ArgumentNullException for null value.");
        }
        catch (ArgumentNullException ex)
        {
            // Assert
            Assert.AreEqual("value", ex.ParamName);
        }
    }

    /// <summary>
    /// Tests that an empty string literal value is preserved.
    /// </summary>
    [TestMethod]
    public void Constructor_WithEmptyValue_PreservesValue()
    {
        // Arrange
        var source = new SourceReference("test.odl");

        // Act
        var token = new StringLiteralToken(source, string.Empty);

        // Assert
        Assert.AreEqual(string.Empty, token.Value);
    }
}
