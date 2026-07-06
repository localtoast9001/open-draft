/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 */
package io.github.localtoast9001.opendraft.lang;

/**
 * Represents a numeric literal token in the OpenDraft language.
 */
public final class NumericLiteralToken extends Token {
    private final Number value;

    /**
     * Constructs a NumericLiteralToken with the specified source reference and numeric value.
     * @param source the source reference of the numeric literal
     * @param value the numeric value
     * @throws IllegalArgumentException if value is null
     */
    public NumericLiteralToken(SourceReference source, Number value) {
        super(source);
        if (value == null) {
            throw new IllegalArgumentException("Numeric literal cannot be null");
        }

        this.value = value;
    }

    /**
     * Returns the numeric value of this token.
     * @return the numeric value
     */
    public Number getValue() {
        return value;
    }

    @Override
    public String toString() {
        return "NumericLiteralToken{"
            + "value=" + value
            + '}';
    }
}
