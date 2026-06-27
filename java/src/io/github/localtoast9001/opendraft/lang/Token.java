/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 * Licensed under the MIT License. See LICENSE.md in the project root for license information.
 */
package io.github.localtoast9001.opendraft.lang;

/**
 * Represents a token in the OpenDraft language.
 */
public abstract class Token {
    /** The source reference for the token. */
    private final SourceReference source;

    /**
     * Creates a new instance of the Token class.
     * @param source The source reference for the token.
     * @throws IllegalArgumentException if source is null.
     */
    public Token(final SourceReference source) {
        if (source == null) {
            throw new IllegalArgumentException("source cannot be null");
        }

        this.source = source;
    }

    /**
     * Gets the source reference for the token.
     * @return The source reference.
     */
    public SourceReference getSource() {
        return this.source;
    }
}
