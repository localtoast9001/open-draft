/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 */
package io.github.localtoast9001.opendraft.lang;

/**
 * Represents a keyword token in the OpenDraft language.
 */
public class KeywordToken extends Token {
    private final Keyword value;

    public KeywordToken(SourceReference source, Keyword value) {
        super(source);
        if (value == null) {
            throw new IllegalArgumentException("Value cannot be null");
        }
        this.value = value;
    }

    public Keyword getValue() {
        return value;
    }

    @Override
    public String toString() {
        return "KeywordToken{" +
                "value=" + value +
                '}';
    }
}
