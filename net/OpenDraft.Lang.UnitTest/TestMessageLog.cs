// <copyright file="TestMessageLog.cs" company="Jon Rowlett">
// Copyright (c) Jon Rowlett. All rights reserved.
// </copyright>

namespace OpenDraft.Lang.UnitTest;

using System.Collections.Generic;

/// <summary>
/// A simple message log for testing purposes.
/// </summary>
public class TestMessageLog
{
    private readonly List<Message> messages = new();

    /// <summary>
    /// Gets all logged messages.
    /// </summary>
    public IReadOnlyList<Message> Messages => this.messages;

    /// <summary>
    /// Logs a message.
    /// </summary>
    /// <param name="message">The message to log.</param>
    public void Log(Message message)
    {
        this.messages.Add(message);
    }

    /// <summary>
    /// Asserts that no messages have been logged.
    /// </summary>
    public void AssertClean()
    {
        if (this.messages.Count != 0)
        {
            var allMessages = string.Join(", ", this.messages);
            Assert.Fail($"Expected no messages to be logged, but found {this.messages.Count}: {allMessages}.");
        }
   }
}
