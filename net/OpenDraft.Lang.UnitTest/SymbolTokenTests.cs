// <copyright file="SymbolTokenTests.cs" company="Jon Rowlett">
// Copyright (c) Jon Rowlett. All rights reserved.
// </copyright>

namespace OpenDraft.Lang.UnitTest;

/// <summary>
/// Unit tests for the <see cref="SymbolToken"/> class.
/// </summary>
[TestClass]
public class SymbolTokenTests
{
    /// <summary>
    /// Tests that a <see cref="SymbolToken"/> can be created with valid source and symbol value.
    /// </summary>
    [TestMethod]
    public void Constructor_WithValidSourceAndValue_CreatesInstance()
    {
        // Arrange
        var source = new SourceReference("test.odl", 1, 2);
        var value = Symbol.LeftBrace;

        // Act
        var token = new SymbolToken(source, value);

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
            _ = new SymbolToken(null!, Symbol.Semicolon);
            Assert.Fail("Expected ArgumentNullException for null source.");
        }
        catch (ArgumentNullException ex)
        {
            // Assert
            Assert.AreEqual("source", ex.ParamName);
        }
    }

    /// <summary>
    /// Tests that Symbol.None value is preserved.
    /// </summary>
    [TestMethod]
    public void Constructor_WithNoneValue_PreservesValue()
    {
        // Arrange
        var source = new SourceReference("test.odl");

        // Act
        var token = new SymbolToken(source, Symbol.None);

        // Assert
        Assert.AreEqual(Symbol.None, token.Value);
    }

    /// <summary>
    /// Tests that different symbol values are preserved.
    /// </summary>
    [TestMethod]
    public void Constructor_WithDifferentValues_PreservesValue()
    {
        // Arrange
        var source = new SourceReference("test.odl");

        // Act and Assert
        Assert.AreEqual(Symbol.RightParen, new SymbolToken(source, Symbol.RightParen).Value);
        Assert.AreEqual(Symbol.Dot, new SymbolToken(source, Symbol.Dot).Value);
        Assert.AreEqual(Symbol.GreaterThanOrEqual, new SymbolToken(source, Symbol.GreaterThanOrEqual).Value);
    }
}
