/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 */
package io.github.localtoast9001.opendraft.lang;

/**
 * Represents a symbol token in the OpenDraft language.
 */
public final class SymbolToken extends Token {
    private final Symbol symbol;

    /**
     * Creates a new instance of the SymbolToken class.
     * @param source The source reference of the token.
     * @param value The symbol value of the token.
     * @throws IllegalArgumentException if value is null or empty.
     */
    public SymbolToken(SourceReference source, Symbol value) {
        super(source);
        if (value == null) {
            throw new IllegalArgumentException("Symbol cannot be null or empty");
        }
        this.symbol = value;
    }

    /**
     * Returns the symbol of this token.
     * @return the symbol
     */
    public Symbol getSymbol() {
        return symbol;
    }

    @Override
    public String toString() {
        return "SymbolToken{"
            + "symbol='"
            + symbol + '\''
            + '}';
    }
}
