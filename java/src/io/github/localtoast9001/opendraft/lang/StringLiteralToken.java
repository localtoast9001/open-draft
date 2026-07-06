/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 */
package io.github.localtoast9001.opendraft.lang;

/**
 * Represents a string literal token in the OpenDraft language.
 */
public class StringLiteralToken extends Token {
    private final String value;

    public StringLiteralToken(SourceReference source, String value) {
        super(source);
        if (value == null) {
            throw new IllegalArgumentException("Value cannot be null");
        }
        this.value = value;
    }

    public String getValue() {
        return value;
    }

    @Override
    public String toString() {
        return "StringLiteralToken{" +
                "value='" + value + '\'' +
                '}';
    }
    
}
