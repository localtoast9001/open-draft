// <copyright file="Message.cs" company="Jon Rowlett">
// Copyright (c) Jon Rowlett. All rights reserved.
// </copyright>

namespace OpenDraft.Lang;

/// <summary>
/// Represents a message produced by any of the language components.
/// </summary>
public class Message
{
    /// <summary>
    /// Initializes a new instance of the <see cref="Message"/> class.
    /// </summary>
    /// <param name="severity">The severity of the message.</param>
    /// <param name="id">The ID of the message.</param>
    /// <param name="source">The source reference for the message.</param>
    /// <param name="text">The text of the message.</param>
    /// <exception cref="ArgumentNullException">Thrown if <paramref name="source"/> or <paramref name="text"/> is <c>null</c>.</exception>
    public Message(
        MessageSeverity severity,
        MessageId id,
        SourceReference source,
        string text)
    {
        this.Severity = severity;
        this.Id = id;
        this.Source = source ?? throw new ArgumentNullException(nameof(source));
        this.Text = text ?? throw new ArgumentNullException(nameof(text));
    }

    /// <summary>
    /// Gets the severity of this message.
    /// </summary>
    public MessageSeverity Severity { get; }

    /// <summary>
    /// Gets the ID of this message.
    /// </summary>
    public MessageId Id { get; }

    /// <summary>
    /// Gets the source reference for this message.
    /// </summary>
    public SourceReference Source { get; }

    /// <summary>
    /// Gets the text of the message.
    /// </summary>
    public string Text { get; }

    /// <inheritdoc/>
    public override string ToString()
    {
        return $"{this.Source}: {this.Severity} {this.Id}: {this.Text}";
    }
}