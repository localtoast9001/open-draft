/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 */
package io.github.localtoast9001.opendraft.lang;

/**
 * Represents an identifier token in the OpenDraft language.
 */
public class IdentifierToken extends Token {
    private final String name;

    public IdentifierToken(SourceReference source, String name) {
        super(source);
        if (name == null || name.isEmpty()) {
            throw new IllegalArgumentException("Identifier cannot be null or empty");
        }
        this.name = name;
    }

    public String getName() {
        return name;
    }

    @Override
    public String toString() {
        return "IdentifierToken{" +
                "name='" + name + '\'' +
                '}';
    }
}
