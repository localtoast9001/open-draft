/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 */
package io.github.localtoast9001.opendraft.lang;

/**
 * Represents a message generated during the processing of OpenDraft source code.
 */
public class Message {
    public final SourceReference source;
    public final MessageId id;
    public final MessageSeverity severity;
    public final String text;

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

    public SourceReference getSource() {
        return source;
    }

    public MessageId getId() {
        return id;
    }

    public MessageSeverity getSeverity() {
        return severity;
    }

    public String getText() {
        return text;
    }

    @Override
    public String toString() {
        return String.format("%s: %s: %s: %s", source, id, severity, text);
    }
}
