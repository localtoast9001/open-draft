/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 */
package io.github.localtoast9001.opendraft.lang;

/**
 * Represents a string literal token in the OpenDraft language.
 */
public final class StringLiteralToken extends Token {
    private final String value;

    /**
     * Creates a new instance of the StringLiteralToken class.
     * @param source The source reference of the token.
     * @param value The string value of the token.
     * @throws IllegalArgumentException if value is null.
     */
    public StringLiteralToken(SourceReference source, String value) {
        super(source);
        if (value == null) {
            throw new IllegalArgumentException("Value cannot be null");
        }
        this.value = value;
    }

    /**
     * Returns the string value of this token.
     * @return the string value
     */
    public String getValue() {
        return value;
    }

    @Override
    public String toString() {
        return "StringLiteralToken{"
            + "value='" + value + '\''
            + '}';
    }
}
