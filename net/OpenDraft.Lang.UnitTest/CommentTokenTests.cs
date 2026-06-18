// <copyright file="CommentTokenTests.cs" company="Jon Rowlett">
// Copyright (c) Jon Rowlett. All rights reserved.
// </copyright>

namespace OpenDraft.Lang.UnitTest;

/// <summary>
/// Unit tests for the <see cref="CommentToken"/> class.
/// </summary>
[TestClass]
public class CommentTokenTests
{
    /// <summary>
    /// Tests that a line <see cref="CommentToken"/> can be created with valid source and text.
    /// </summary>
    [TestMethod]
    public void Constructor_WithLineComment_CreatesInstance()
    {
        // Arrange
        var source = new SourceReference("test.odl", 1, 2);
        var text = "line comment";

        // Act
        var token = new CommentToken(source, text, false);

        // Assert
        Assert.AreSame(source, token.Source);
        Assert.AreEqual(text, token.Text);
        Assert.IsFalse(token.IsBlock);
    }

    /// <summary>
    /// Tests that a block <see cref="CommentToken"/> can be created with valid source and text.
    /// </summary>
    [TestMethod]
    public void Constructor_WithBlockComment_CreatesInstance()
    {
        // Arrange
        var source = new SourceReference("test.odl", 3, 4, 5, 6);
        var text = "block comment";

        // Act
        var token = new CommentToken(source, text, true);

        // Assert
        Assert.AreSame(source, token.Source);
        Assert.AreEqual(text, token.Text);
        Assert.IsTrue(token.IsBlock);
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
            _ = new CommentToken(null!, "comment", false);
            Assert.Fail("Expected ArgumentNullException for null source.");
        }
        catch (ArgumentNullException ex)
        {
            // Assert
            Assert.AreEqual("source", ex.ParamName);
        }
    }

    /// <summary>
    /// Tests that constructor throws when text is null.
    /// </summary>
    [TestMethod]
    public void Constructor_WithNullText_ThrowsException()
    {
        try
        {
            // Arrange
            var source = new SourceReference("test.odl");

            // Act
            _ = new CommentToken(source, null!, false);
            Assert.Fail("Expected ArgumentNullException for null text.");
        }
        catch (ArgumentNullException ex)
        {
            // Assert
            Assert.AreEqual("text", ex.ParamName);
        }
    }

    /// <summary>
    /// Tests that an empty comment text is preserved.
    /// </summary>
    [TestMethod]
    public void Constructor_WithEmptyText_PreservesValue()
    {
        // Arrange
        var source = new SourceReference("test.odl");

        // Act
        var token = new CommentToken(source, string.Empty, false);

        // Assert
        Assert.AreEqual(string.Empty, token.Text);
        Assert.IsFalse(token.IsBlock);
    }
}
