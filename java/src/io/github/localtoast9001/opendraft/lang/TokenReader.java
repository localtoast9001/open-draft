/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 */
package io.github.localtoast9001.opendraft.lang;

import java.io.InputStreamReader;

/**
 * Reads tokens from a source.
 */
public class TokenReader {
    private final InputStreamReader inner;

    /**
     * Creates a new instance of the TokenReader class.
     * @param inner The input stream reader to read tokens from.
     * @throws IllegalArgumentException if inner is null.
     */
    public TokenReader(final InputStreamReader inner) {
        if (inner == null) {
            throw new IllegalArgumentException("inner cannot be null");
        }

        this.inner = inner;
    }
}
