/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 */
package io.github.localtoast9001.opendraft.lang;

/**
 * Represents a comment token in the OpenDraft language.
 */
public final class CommentToken extends Token {
    private final String text;

    /**
     * Constructs a CommentToken with the specified source reference and comment text.
     * @param source the source reference of the comment
     * @param text the text of the comment
     */
    public CommentToken(SourceReference source, String text) {
        super(source);
        if (text == null) {
            throw new IllegalArgumentException("Comment text cannot be null");
        }

        this.text = text;
    }

    /**
     * Returns the text of the comment.
     * @return the text of the comment.
     */
    public String getText() {
        return text;
    }

    @Override
    public String toString() {
        return "CommentToken{" + "text='" + text + '\'' + '}';
    }
}
