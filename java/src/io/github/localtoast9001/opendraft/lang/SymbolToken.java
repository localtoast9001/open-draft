/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 */
package io.github.localtoast9001.opendraft.lang;

/**
 * Represents a symbol token in the OpenDraft language.
 */
public class SymbolToken extends Token {
    private final Symbol symbol;

    public SymbolToken(SourceReference source, Symbol value) {
        super(source);
        if (value == null) {
            throw new IllegalArgumentException("Symbol cannot be null or empty");
        }
        this.symbol = value;
    }

    public Symbol getSymbol() {
        return symbol;
    }

    @Override
    public String toString() {
        return "SymbolToken{" +
                "symbol='" + symbol + '\'' +
                '}';
    }
}
