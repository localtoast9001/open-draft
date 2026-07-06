/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 */
package io.github.localtoast9001.opendraft.lang;

/**
 * Represents a unique identifier for a message.
 * A MessageId consists of a category and a code.
 */
public final class MessageId {
    private static final int MAX_CODE = 9999;
    private static final int MAX_CATEGORY_LENGTH = 4;
    private final String category;
    private final int code;

    /**
     * Constructs a MessageId with the specified category and code.
     * @param category the category of the message
     * @param code the code of the message
     */
    public MessageId(String category, int code) {
        if (category == null || !(category.length() <= MAX_CATEGORY_LENGTH && category.length() > 0)) {
            throw new IllegalArgumentException("Category must be between 1 and " + MAX_CATEGORY_LENGTH + " characters");
        }

        if (code < 0 || code > MAX_CODE) {
            throw new IllegalArgumentException("Code must be between 0 and " + MAX_CODE);
        }

        this.category = category;
        this.code = code;
    }

    /**
     * Returns the category of this message ID.
     * @return the category
     */
    public String getCategory() {
        return category;
    }

    /**
     * Returns the code of this message ID.
     * @return the code
     */
    public int getCode() {
        return code;
    }

    @Override
    public String toString() {
        return category + String.format("%04d", code);
    }
}
