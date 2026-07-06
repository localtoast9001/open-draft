/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 */
package io.github.localtoast9001.opendraft.lang;

/**
 * Represents a unique identifier for a message.
 * A MessageId consists of a category and a code.
 */
public class MessageId {
    private final String category;
    private final int code;

    public MessageId(String category, int code) {
        if (category == null || !(category.length() <= 4 && category.length() > 0)) {
            throw new IllegalArgumentException("Category must be no more than 4 characters");
        }

        if (code < 0 || code > 9999) {
            throw new IllegalArgumentException("Code must be between 0 and 9999");
        }

        this.category = category;
        this.code = code;
    }

    public String getCategory() {
        return category;
    }

    public int getCode() {
        return code;
    }

    @Override
    public String toString() {
        return category + String.format("%04d", code);
    }
}
