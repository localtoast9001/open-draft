/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 */
package io.github.localtoast9001.opendraft.lang;

/**
 * Represents a message generated during the processing of OpenDraft source code.
 */
public final class Message {
    private final SourceReference source;
    private final MessageId id;
    private final MessageSeverity severity;
    private final String text;

    /**
     * Constructs a Message with the specified source reference, message ID, severity, and text.
     * @param source the source reference of the message
     * @param id the message ID
     * @param severity the severity of the message
     * @param text the text of the message
     */
    public Message(
        final SourceReference source,
        final MessageId id,
        final MessageSeverity severity,
        final String text) {
        if (source == null) {
            throw new IllegalArgumentException("source cannot be null");
        }

        if (id == null) {
            throw new IllegalArgumentException("id cannot be null");
        }

        if (severity == null) {
            throw new IllegalArgumentException("severity cannot be null");
        }

        if (text == null) {
            throw new IllegalArgumentException("text cannot be null");
        }

        this.source = source;
        this.id = id;
        this.severity = severity;
        this.text = text;
    }

    /**
     * Returns the source reference of this message.
     * @return the source reference
     */
    public SourceReference getSource() {
        return source;
    }

    /**
     * Returns the message ID of this message.
     * @return the message ID
     */
    public MessageId getId() {
        return id;
    }

    /**
     * Returns the severity of this message.
     * @return the severity
     */
    public MessageSeverity getSeverity() {
        return severity;
    }

    /**
     * Returns the text of this message.
     * @return the text
     */
    public String getText() {
        return text;
    }

    @Override
    public String toString() {
        return String.format("%s: %s: %s: %s", source, id, severity, text);
    }
}
