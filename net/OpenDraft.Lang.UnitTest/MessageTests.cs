// <copyright file="MessageTests.cs" company="Jon Rowlett">
// Copyright (c) Jon Rowlett. All rights reserved.
// </copyright>

namespace OpenDraft.Lang.UnitTest;

/// <summary>
/// Unit tests for the <see cref="Message"/> class.
/// </summary>
[TestClass]
public class MessageTests
{
    /// <summary>
    /// Tests that a <see cref="Message"/> can be created with valid constructor arguments.
    /// </summary>
    [TestMethod]
    public void Constructor_WithValidArguments_CreatesInstance()
    {
        // Arrange
        var severity = MessageSeverity.Warning;
        var id = new MessageId("ODL", 1234);
        var source = new SourceReference("test.odl", 5, 10);
        var text = "Test message.";

        // Act
        var message = new Message(severity, id, source, text);

        // Assert
        Assert.AreEqual(severity, message.Severity);
        Assert.AreEqual(id, message.Id);
        Assert.AreSame(source, message.Source);
        Assert.AreEqual(text, message.Text);
    }

    /// <summary>
    /// Tests that constructor throws when source is null.
    /// </summary>
    [TestMethod]
    public void Constructor_WithNullSource_ThrowsException()
    {
        try
        {
            // Arrange
            var id = new MessageId("ODL", 1000);

            // Act
            _ = new Message(MessageSeverity.Error, id, null!, "A message");
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
            var id = new MessageId("ODL", 1000);
            var source = new SourceReference("test.odl", 5, 10);

            // Act
            _ = new Message(MessageSeverity.Error, id, source, null!);
            Assert.Fail("Expected ArgumentNullException for null text.");
        }
        catch (ArgumentNullException ex)
        {
            // Assert
            Assert.AreEqual("text", ex.ParamName);
        }
    }

    /// <summary>
    /// Tests that ToString() includes source, severity, id, and text.
    /// </summary>
    [TestMethod]
    public void ToString_WithValidMessage_ReturnsExpectedFormat()
    {
        // Arrange
        var id = new MessageId("ODL", 1000);
        var source = new SourceReference("test.odl", 5, 10);
        var message = new Message(MessageSeverity.Error, id, source, "Unterminated string literal.");

        // Act
        var result = message.ToString();

        // Assert
        Assert.AreEqual("test.odl(5,10): Error ODL1000: Unterminated string literal.", result);
    }

    /// <summary>
    /// Tests that ToString() with source path only still formats correctly.
    /// </summary>
    [TestMethod]
    public void ToString_WithPathOnlySource_ReturnsExpectedFormat()
    {
        // Arrange
        var id = new MessageId("ODL", 42);
        var source = new SourceReference("test.odl");
        var message = new Message(MessageSeverity.Info, id, source, "Info text");

        // Act
        var result = message.ToString();

        // Assert
        Assert.AreEqual("test.odl: Info ODL0042: Info text", result);
    }
}
