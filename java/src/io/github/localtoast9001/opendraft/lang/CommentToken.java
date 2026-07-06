/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 */
package io.github.localtoast9001.opendraft.lang;

/**
 * Represents a comment token in the OpenDraft language.
 */
public class CommentToken extends Token {
    private final String text;

    public CommentToken(SourceReference source, String text) {
        super(source);
        if (text == null) {
            throw new IllegalArgumentException("Comment text cannot be null");
        }
        this.text = text;
    }

    public String getText() {
        return text;
    }

    @Override
    public String toString() {
        return "CommentToken{" +
                "text='" + text + '\'' +
                '}';
    }  
}
