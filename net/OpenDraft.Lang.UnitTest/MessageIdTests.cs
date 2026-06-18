// <copyright file="MessageIdTests.cs" company="Jon Rowlett">
// Copyright (c) Jon Rowlett. All rights reserved.
// </copyright>

namespace OpenDraft.Lang.UnitTest;

/// <summary>
/// Unit tests for the <see cref="MessageId"/> struct.
/// </summary>
[TestClass]
public class MessageIdTests
{
    /// <summary>
    /// Tests that <see cref="MessageId"/> can be created with valid values.
    /// </summary>
    [TestMethod]
    public void Constructor_WithValidValues_CreatesInstance()
    {
        // Arrange
        var category = "ODL";
        var code = 1000;

        // Act
        var id = new MessageId(category, code);

        // Assert
        Assert.AreEqual(category, id.Category);
        Assert.AreEqual(code, id.Code);
    }

    /// <summary>
    /// Tests that constructor throws when category is null.
    /// </summary>
    [TestMethod]
    public void Constructor_WithNullCategory_ThrowsException()
    {
        try
        {
            // Act
            _ = new MessageId(null!, 1000);
            Assert.Fail("Expected ArgumentNullException for null category.");
        }
        catch (ArgumentNullException ex)
        {
            // Assert
            Assert.AreEqual("category", ex.ParamName);
        }
    }

    /// <summary>
    /// Tests ToString() formats category and zero-padded 4-digit code.
    /// </summary>
    [TestMethod]
    public void ToString_WithTypicalCode_FormatsAsExpected()
    {
        // Arrange
        var id = new MessageId("ODL", 42);

        // Act
        var text = id.ToString();

        // Assert
        Assert.AreEqual("ODL0042", text);
    }

    /// <summary>
    /// Tests ToString() for code values requiring more than 4 digits.
    /// </summary>
    [TestMethod]
    public void ToString_WithLongCode_FormatsAsExpected()
    {
        // Arrange
        var id = new MessageId("ODL", 12345);

        // Act
        var text = id.ToString();

        // Assert
        Assert.AreEqual("ODL12345", text);
    }

    /// <summary>
    /// Tests equality members for equivalent instances.
    /// </summary>
    [TestMethod]
    public void Equals_WithSameValues_ReturnsTrue()
    {
        // Arrange
        var left = new MessageId("ODL", 1000);
        var right = new MessageId("ODL", 1000);

        // Act and Assert
        Assert.IsTrue(left.Equals(right));
        Assert.IsTrue(left.Equals((object)right));
        Assert.IsTrue(left == right);
        Assert.IsFalse(left != right);
    }

    /// <summary>
    /// Tests equality members for different instances.
    /// </summary>
    [TestMethod]
    public void Equals_WithDifferentValues_ReturnsFalse()
    {
        // Arrange
        var left = new MessageId("ODL", 1000);
        var differentCategory = new MessageId("ABC", 1000);
        var differentCode = new MessageId("ODL", 1001);

        // Act and Assert
        Assert.IsFalse(left.Equals(differentCategory));
        Assert.IsFalse(left.Equals(differentCode));
        Assert.IsFalse(left == differentCategory);
        Assert.IsTrue(left != differentCategory);
        Assert.IsFalse(left == differentCode);
        Assert.IsTrue(left != differentCode);
    }

    /// <summary>
    /// Tests Equals(object) with a non-MessageId value.
    /// </summary>
    [TestMethod]
    public void EqualsObject_WithDifferentType_ReturnsFalse()
    {
        // Arrange
        var id = new MessageId("ODL", 1000);

        // Act
        var result = id.Equals("ODL1000");

        // Assert
        Assert.IsFalse(result);
    }

    /// <summary>
    /// Tests that equal values produce the same hash code.
    /// </summary>
    [TestMethod]
    public void GetHashCode_WithEqualValues_Matches()
    {
        // Arrange
        var left = new MessageId("ODL", 1000);
        var right = new MessageId("ODL", 1000);

        // Act and Assert
        Assert.AreEqual(left.GetHashCode(), right.GetHashCode());
    }

    /// <summary>
    /// Tests CompareTo() and relational operators when categories differ.
    /// </summary>
    [TestMethod]
    public void CompareTo_WithDifferentCategories_UsesOrdinalCategoryComparison()
    {
        // Arrange
        var left = new MessageId("ABC", 2000);
        var right = new MessageId("ODL", 1000);

        // Act and Assert
        Assert.IsLessThan(0, left.CompareTo(right));
        Assert.IsTrue(left < right);
        Assert.IsTrue(left <= right);
        Assert.IsFalse(left > right);
        Assert.IsFalse(left >= right);
    }

    /// <summary>
    /// Tests CompareTo() and relational operators when categories match.
    /// </summary>
    [TestMethod]
    public void CompareTo_WithSameCategory_UsesCodeComparison()
    {
        // Arrange
        var left = new MessageId("ODL", 1000);
        var right = new MessageId("ODL", 1001);

        // Act and Assert
        Assert.IsLessThan(0, left.CompareTo(right));
        Assert.IsTrue(left < right);
        Assert.IsTrue(left <= right);
        Assert.IsFalse(left > right);
        Assert.IsFalse(left >= right);
    }

    /// <summary>
    /// Tests CompareTo() and relational operators for equal values.
    /// </summary>
    [TestMethod]
    public void CompareTo_WithEqualValues_ReturnsZeroAndRelationalOperatorsMatch()
    {
        // Arrange
        var left = new MessageId("ODL", 1000);
        var right = new MessageId("ODL", 1000);

        // Act and Assert
        Assert.AreEqual(0, left.CompareTo(right));
        Assert.IsTrue(left <= right);
        Assert.IsTrue(left >= right);
        Assert.IsFalse(left < right);
        Assert.IsFalse(left > right);
    }
}
