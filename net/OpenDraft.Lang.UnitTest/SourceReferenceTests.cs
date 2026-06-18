// <copyright file="SourceReferenceTests.cs" company="Jon Rowlett">
// Copyright (c) Jon Rowlett. All rights reserved.
// </copyright>

namespace OpenDraft.Lang.UnitTest;

/// <summary>
/// Unit tests for the <see cref="SourceReference"/> class.
/// </summary>
[TestClass]
public class SourceReferenceTests
{
    /// <summary>
    /// Tests that a <see cref="SourceReference"/> can be created with a valid path.
    /// </summary>
    [TestMethod]
    public void Constructor_WithValidPath_CreatesInstance()
    {
        // Arrange
        var path = "test.odl";

        // Act
        var reference = new SourceReference(path);

        // Assert
        Assert.AreEqual(path, reference.Path);
        Assert.AreEqual(0, reference.LineNumber);
        Assert.AreEqual(0, reference.ColumnNumber);
        Assert.AreEqual(0, reference.EndLineNumber);
        Assert.AreEqual(0, reference.EndColumnNumber);
    }

    /// <summary>
    /// Tests that a <see cref="SourceReference"/> can be created with line and column numbers.
    /// </summary>
    [TestMethod]
    public void Constructor_WithLineAndColumn_CreatesInstance()
    {
        // Arrange
        var path = "test.odl";
        var lineNumber = 5;
        var columnNumber = 10;

        // Act
        var reference = new SourceReference(path, lineNumber, columnNumber);

        // Assert
        Assert.AreEqual(path, reference.Path);
        Assert.AreEqual(lineNumber, reference.LineNumber);
        Assert.AreEqual(columnNumber, reference.ColumnNumber);
        Assert.AreEqual(lineNumber, reference.EndLineNumber);
        Assert.AreEqual(columnNumber, reference.EndColumnNumber);
    }

    /// <summary>
    /// Tests that a <see cref="SourceReference"/> can be created with end line and column numbers.
    /// </summary>
    [TestMethod]
    public void Constructor_WithEndLineAndColumn_CreatesInstance()
    {
        // Arrange
        var path = "test.odl";
        var lineNumber = 5;
        var columnNumber = 10;
        var endLineNumber = 7;
        var endColumnNumber = 20;

        // Act
        var reference = new SourceReference(path, lineNumber, columnNumber, endLineNumber, endColumnNumber);

        // Assert
        Assert.AreEqual(path, reference.Path);
        Assert.AreEqual(lineNumber, reference.LineNumber);
        Assert.AreEqual(columnNumber, reference.ColumnNumber);
        Assert.AreEqual(endLineNumber, reference.EndLineNumber);
        Assert.AreEqual(endColumnNumber, reference.EndColumnNumber);
    }

    /// <summary>
    /// Tests that end line number defaults to line number when not provided.
    /// </summary>
    [TestMethod]
    public void Constructor_WhenEndLineIsZero_DefaultsToLineNumber()
    {
        // Arrange
        var path = "test.odl";
        var lineNumber = 5;
        var columnNumber = 10;

        // Act
        var reference = new SourceReference(path, lineNumber, columnNumber, 0, 20);

        // Assert
        Assert.AreEqual(lineNumber, reference.EndLineNumber);
        Assert.AreEqual(20, reference.EndColumnNumber);
    }

    /// <summary>
    /// Tests that end column number defaults to column number when not provided.
    /// </summary>
    [TestMethod]
    public void Constructor_WhenEndColumnIsZero_DefaultsToColumnNumber()
    {
        // Arrange
        var path = "test.odl";
        var lineNumber = 5;
        var columnNumber = 10;

        // Act
        var reference = new SourceReference(path, lineNumber, columnNumber, 7, 0);

        // Assert
        Assert.AreEqual(7, reference.EndLineNumber);
        Assert.AreEqual(columnNumber, reference.EndColumnNumber);
    }

    /// <summary>
    /// Tests that constructor throws when path is null.
    /// </summary>
    [TestMethod]
    public void Constructor_WithNullPath_ThrowsException()
    {
        try
        {
            // Act
            _ = new SourceReference(null!);
            Assert.Fail("Expected ArgumentOutOfRangeException for null path.");
        }
        catch (ArgumentOutOfRangeException ex)
        {
            // Assert
            Assert.AreEqual("path", ex.ParamName);
            StringAssert.Contains(ex.Message, "Path cannot be null or empty.");
        }
    }

    /// <summary>
    /// Tests that constructor throws when path is empty.
    /// </summary>
    [TestMethod]
    public void Constructor_WithEmptyPath_ThrowsException()
    {
        try
        {
            // Act
            _ = new SourceReference(string.Empty);
            Assert.Fail("Expected ArgumentOutOfRangeException for empty path.");
        }
        catch (ArgumentOutOfRangeException ex)
        {
            // Assert
            Assert.AreEqual("path", ex.ParamName);
            StringAssert.Contains(ex.Message, "Path cannot be null or empty.");
        }
    }

    /// <summary>
    /// Tests the ToString() method with only path.
    /// </summary>
    [TestMethod]
    public void ToString_WithOnlyPath_ReturnsPath()
    {
        // Arrange
        var path = "test.odl";
        var reference = new SourceReference(path);

        // Act
        var result = reference.ToString();

        // Assert
        Assert.AreEqual(path, result);
    }

    /// <summary>
    /// Tests the ToString() method with path and line number.
    /// </summary>
    [TestMethod]
    public void ToString_WithLineNumber_IncludesLineInOutput()
    {
        // Arrange
        var reference = new SourceReference("test.odl", 5);

        // Act
        var result = reference.ToString();

        // Assert
        Assert.AreEqual("test.odl(5)", result);
    }

    /// <summary>
    /// Tests the ToString() method with path, line, and column numbers.
    /// </summary>
    [TestMethod]
    public void ToString_WithLineAndColumn_IncludesLineAndColumnInOutput()
    {
        // Arrange
        var reference = new SourceReference("test.odl", 5, 10);

        // Act
        var result = reference.ToString();

        // Assert
        Assert.AreEqual("test.odl(5,10)", result);
    }

    /// <summary>
    /// Tests the ToString() method with different end line number.
    /// </summary>
    [TestMethod]
    public void ToString_WithDifferentEndLine_IncludesEndLineInOutput()
    {
        // Arrange
        var reference = new SourceReference("test.odl", 5, 10, 7, 10);

        // Act
        var result = reference.ToString();

        // Assert
        Assert.AreEqual("test.odl(5,10,7,10)", result);
    }

    /// <summary>
    /// Tests the ToString() method with different end column but same line.
    /// </summary>
    [TestMethod]
    public void ToString_WithDifferentEndColumn_IncludesEndLineAndColumnInOutput()
    {
        // Arrange
        var reference = new SourceReference("test.odl", 5, 10, 5, 20);

        // Act
        var result = reference.ToString();

        // Assert
        Assert.AreEqual("test.odl(5,10,5,20)", result);
    }

    /// <summary>
    /// Tests the ToString() method with only path and line (column is 0).
    /// </summary>
    [TestMethod]
    public void ToString_WithZeroColumn_OmitsColumnFromOutput()
    {
        // Arrange
        var reference = new SourceReference("test.odl", 5, 0);

        // Act
        var result = reference.ToString();

        // Assert
        Assert.AreEqual("test.odl(5)", result);
    }

    /// <summary>
    /// Tests the ToString() method with line and end line but same column.
    /// </summary>
    [TestMethod]
    public void ToString_WithSameLineAndColumn_OmitsEndCoordinatesFromOutput()
    {
        // Arrange
        var reference = new SourceReference("test.odl", 5, 10, 5, 10);

        // Act
        var result = reference.ToString();

        // Assert
        Assert.AreEqual("test.odl(5,10)", result);
    }

    /// <summary>
    /// Tests that path with special characters is handled correctly.
    /// </summary>
    [TestMethod]
    public void Constructor_WithSpecialCharactersInPath_CreatesInstance()
    {
        // Arrange
        var path = "/path/to/some-file_2024.odl";

        // Act
        var reference = new SourceReference(path, 10, 5);

        // Assert
        Assert.AreEqual(path, reference.Path);
        Assert.AreEqual("/path/to/some-file_2024.odl(10,5)", reference.ToString());
    }

    /// <summary>
    /// Tests that multiple instances with same parameters are independent.
    /// </summary>
    [TestMethod]
    public void MultipleInstances_WithSameParameters_AreIndependent()
    {
        // Arrange
        var path = "test.odl";

        // Act
        var reference1 = new SourceReference(path, 5, 10);
        var reference2 = new SourceReference(path, 5, 10);

        // Assert
        Assert.AreNotSame(reference1, reference2);
        Assert.AreEqual(reference1.Path, reference2.Path);
        Assert.AreEqual(reference1.LineNumber, reference2.LineNumber);
        Assert.AreEqual(reference1.ToString(), reference2.ToString());
    }

    /// <summary>
    /// Tests that end coordinates are properly initialized when both are zero.
    /// </summary>
    [TestMethod]
    public void Constructor_WhenBothEndCoordinatesAreZero_DefaultsToBothStartCoordinates()
    {
        // Arrange
        var path = "test.odl";
        var lineNumber = 5;
        var columnNumber = 10;

        // Act
        var reference = new SourceReference(path, lineNumber, columnNumber, 0, 0);

        // Assert
        Assert.AreEqual(lineNumber, reference.EndLineNumber);
        Assert.AreEqual(columnNumber, reference.EndColumnNumber);
    }
}
