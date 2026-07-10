// <copyright file="NumericLiteralTokenTests.cs" company="Jon Rowlett">
// Copyright (c) Jon Rowlett. All rights reserved.
// </copyright>

namespace OpenDraft.Lang.UnitTest;

/// <summary>
/// Unit tests for the <see cref="NumericLiteralToken"/> class.
/// </summary>
[TestClass]
public class NumericLiteralTokenTests
{
    /// <summary>
    /// Tests that an integer <see cref="NumericLiteralToken"/> can be created with valid source and value.
    /// </summary>
    [TestMethod]
    public void Constructor_WithIntegerValue_CreatesIntegerToken()
    {
        // Arrange
        var source = new SourceReference("test.odl", 1, 2);
        var value = 42L;

        // Act
        var token = new NumericLiteralToken(source, value, "mm");

        // Assert
        Assert.AreSame(source, token.Source);
        Assert.IsFalse(token.IsFloatingPoint);
        Assert.AreEqual(value, token.IntegerValue);
        Assert.AreEqual(0m, token.FloatingPointValue);
        Assert.AreEqual("mm", token.Unit);
    }

    /// <summary>
    /// Tests that a floating-point <see cref="NumericLiteralToken"/> can be created with valid source and value.
    /// </summary>
    [TestMethod]
    public void Constructor_WithFloatingPointValue_CreatesFloatingPointToken()
    {
        // Arrange
        var source = new SourceReference("test.odl", 3, 4);
        var value = 3.14159m;

        // Act
        var token = new NumericLiteralToken(source, value, "mm");

        // Assert
        Assert.AreSame(source, token.Source);
        Assert.IsTrue(token.IsFloatingPoint);
        Assert.AreEqual(0L, token.IntegerValue);
        Assert.AreEqual(value, token.FloatingPointValue, 0.0000001m);
        Assert.AreEqual("mm", token.Unit);
    }

    /// <summary>
    /// Tests that integer constructor throws when source is null.
    /// </summary>
    [TestMethod]
    public void IntegerConstructor_WithNullSource_ThrowsException()
    {
        try
        {
            // Act
            _ = new NumericLiteralToken(null!, 1L);
            Assert.Fail("Expected ArgumentNullException for null source.");
        }
        catch (ArgumentNullException ex)
        {
            // Assert
            Assert.AreEqual("source", ex.ParamName);
        }
    }

    /// <summary>
    /// Tests that floating-point constructor throws when source is null.
    /// </summary>
    [TestMethod]
    public void FloatingPointConstructor_WithNullSource_ThrowsException()
    {
        try
        {
            // Act
            _ = new NumericLiteralToken(null!, 1.0m);
            Assert.Fail("Expected ArgumentNullException for null source.");
        }
        catch (ArgumentNullException ex)
        {
            // Assert
            Assert.AreEqual("source", ex.ParamName);
        }
    }
}
