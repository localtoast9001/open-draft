/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 */
package io.github.localtoast9001.opendraft.lang;

/**
 * Represents a numeric literal token in the OpenDraft language.
 */
public class NumericLiteralToken extends Token {
    private final Number value;

    public NumericLiteralToken(SourceReference source, Number value) {
        super(source);
        if (value == null) {
            throw new IllegalArgumentException("Numeric literal cannot be null");
        }
        this.value = value;
    }

    public Number getValue() {
        return value;
    }

    @Override
    public String toString() {
        return "NumericLiteralToken{" +
                "value=" + value +
                '}';
    }
}
