/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 */
package io.github.localtoast9001.opendraft.lang;

/**
 * Represents a keyword token in the OpenDraft language.
 */
public final class KeywordToken extends Token {
    private final Keyword value;

    /**
     * Constructs a KeywordToken with the specified source reference and keyword value.
     * @param source the source reference of the keyword
     * @param value the keyword value
     */
    public KeywordToken(SourceReference source, Keyword value) {
        super(source);
        if (value == null) {
            throw new IllegalArgumentException("Value cannot be null");
        }
        this.value = value;
    }

    /**
     * Returns the keyword value of this token.
     * @return the keyword value
     */
    public Keyword getValue() {
        return value;
    }

    @Override
    public String toString() {
        return "KeywordToken{" + "value=" + value + '}';
    }
}
