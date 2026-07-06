/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 */
package io.github.localtoast9001.opendraft.lang;

/**
 * Represents an identifier token in the OpenDraft language.
 */
public final class IdentifierToken extends Token {
    private final String name;

    /**
     * Constructs an IdentifierToken with the specified source reference and identifier name.
     * @param source the source reference of the identifier
     * @param name the name of the identifier
     */
    public IdentifierToken(SourceReference source, String name) {
        super(source);
        if (name == null || name.isEmpty()) {
            throw new IllegalArgumentException("Identifier cannot be null or empty");
        }
        this.name = name;
    }

    /**
     * Returns the name of the identifier.
     * @return the name of the identifier
     */
    public String getName() {
        return name;
    }

    @Override
    public String toString() {
        return "IdentifierToken{" + "name='" + name + '\'' + '}';
    }
}
