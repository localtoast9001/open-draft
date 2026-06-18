// <copyright file="MessageUtilityTests.cs" company="Jon Rowlett">
// Copyright (c) Jon Rowlett. All rights reserved.
// </copyright>

namespace OpenDraft.Lang.UnitTest;

/// <summary>
/// Unit tests for the <see cref="MessageUtility"/> class.
/// </summary>
[TestClass]
public class MessageUtilityTests
{
    /// <summary>
    /// Tests that unterminated string literal message id has expected value.
    /// </summary>
    [TestMethod]
    public void UnterminatedStringLiteralMessageId_HasExpectedValue()
    {
        // Act
        var id = MessageUtility.UnterminatedStringLiteralMessageId;

        // Assert
        Assert.AreEqual(Constants.DefaultMessageCategory, id.Category);
        Assert.AreEqual(1000, id.Code);
    }

    /// <summary>
    /// Tests that unterminated string literal helper creates expected message.
    /// </summary>
    [TestMethod]
    public void UnterminatedStringLiteral_WithValidSource_CreatesExpectedMessage()
    {
        // Arrange
        var source = new SourceReference("test.odl", 5, 10);

        // Act
        var message = MessageUtility.UnterminatedStringLiteral(source);

        // Assert
        Assert.AreEqual(MessageSeverity.Error, message.Severity);
        Assert.AreEqual(MessageUtility.UnterminatedStringLiteralMessageId, message.Id);
        Assert.AreSame(source, message.Source);
        Assert.AreEqual("Unterminated string literal.", message.Text);
        Assert.AreEqual("test.odl(5,10): Error ODL1000: Unterminated string literal.", message.ToString());
    }

    /// <summary>
    /// Tests that unterminated string literal helper throws when source is null.
    /// </summary>
    [TestMethod]
    public void UnterminatedStringLiteral_WithNullSource_ThrowsException()
    {
        try
        {
            // Act
            _ = MessageUtility.UnterminatedStringLiteral(null!);
            Assert.Fail("Expected ArgumentNullException for null source.");
        }
        catch (ArgumentNullException ex)
        {
            // Assert
            Assert.AreEqual("source", ex.ParamName);
        }
    }
}
