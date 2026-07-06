/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 */
package io.github.localtoast9001.opendraft.lang;

import java.io.InputStreamReader;
import java.util.function.Consumer;

/**
 * Reads tokens from a source.
 */
public final class TokenReader {
    private final WrappedInputStreamReader inner;
    private final Consumer<Message> messageCallback;
    private Token peekedToken;

    /**
     * Creates a new instance of the TokenReader class.
     * @param inner The input stream reader to read tokens from.
     * @param startSource The source reference to use for the first token.
     * @param messageCallback The callback to use for messages.
     * @throws IllegalArgumentException if inner is null.
     */
    public TokenReader(
        final InputStreamReader inner,
        final SourceReference startSource,
        final Consumer<Message> messageCallback) {
        if (inner == null) {
            throw new IllegalArgumentException("inner cannot be null");
        }

        this.inner = new WrappedInputStreamReader(inner, startSource);
        this.messageCallback = messageCallback;
    }

    /**
     * Returns the current source reference of the token reader.
     * @return the current source reference
     */
    public SourceReference getCurrentSource() {
        return inner.getCurrentSource();
    }

    /**
     * Peeks at the next token without consuming it.
     * @return the next token
     * @throws java.io.IOException if an I/O error occurs
     */
    public Token peek() throws java.io.IOException {
        if (this.peekedToken == null) {
            this.peekedToken = innerRead();
        }

        return this.peekedToken;
    }

    /**
     * Reads and consumes the next token.
     * @return the next token
     * @throws java.io.IOException if an I/O error occurs
     */
    public Token read() throws java.io.IOException {
        Token result = peek();
        this.peekedToken = null;
        return result;
    }

    private static boolean isWhitespace(int ch) {
        return ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r';
    }

    private static boolean isIdentifierStart(int ch) {
        return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || ch == '_';
    }

    private static boolean isDigit(int ch) {
        return ch >= '0' && ch <= '9';
    }

    private Token innerRead() throws java.io.IOException {
        skipWhitespace();
        int ch = inner.peek();
        if (isIdentifierStart(ch)) {
            return readIdentifierOrKeyword();
        } else if (isDigit(ch)) {
            return readNumericLiteral();
        } else if (ch == '"') {
            return readStringLiteral();
        } else {
            return readSymbol();
        }
    }

    private Token readIdentifierOrKeyword() throws java.io.IOException {
        StringBuilder sb = new StringBuilder();
        SourceReference startSource = inner.getCurrentSource();
        int ch = inner.peek();
        while (isIdentifierStart(ch) || isDigit(ch)) {
            sb.append((char) inner.read());
            ch = inner.peek();
        }

        String name = sb.toString();
        Keyword keyword = Keyword.fromString(name);
        if (keyword != Keyword.UNDEFINED) {
            return new KeywordToken(startSource, keyword);
        } else {
            return new IdentifierToken(startSource, name);
        }
    }

    private Token readNumericLiteral() throws java.io.IOException {
        StringBuilder sb = new StringBuilder();
        SourceReference startSource = inner.getCurrentSource();
        int ch = inner.peek();
        while (isDigit(ch)) {
            sb.append((char) inner.read());
            ch = inner.peek();
        }

        String value = sb.toString();
        return new NumericLiteralToken(startSource, Integer.parseInt(value));
    }

    private Token readStringLiteral() throws java.io.IOException {
        StringBuilder sb = new StringBuilder();
        SourceReference startSource = inner.getCurrentSource();
        int ch = inner.read(); // consume the opening quote
        if (ch != '"') {
            throw new IllegalStateException("Expected opening quote for string literal");
        }

        ch = inner.peek();
        while (ch != '"') {
            if (ch == -1) {
                throw new IllegalStateException("Unexpected end of input while reading string literal");
            }
            sb.append((char) inner.read());
            ch = inner.peek();
        }

        inner.read(); // consume the closing quote
        String value = sb.toString();
        return new StringLiteralToken(startSource, value);
    }

    private Token readSymbol() throws java.io.IOException {
        SourceReference startSource = inner.getCurrentSource();
        int ch = inner.read();
        if (ch == -1) {
            return null; // End of input
        }

        Symbol symbol = Symbol.fromString(Character.toString((char) ch));
        return new SymbolToken(startSource, symbol);
    }

    private void skipWhitespace() throws java.io.IOException {
        int ch = inner.peek();
        while (isWhitespace(ch)) {
            inner.read();
            ch = inner.peek();
        }
    }

    private final class WrappedInputStreamReader {
        private final InputStreamReader inner;
        private SourceReference startSource;
        private int peekedChar = -1;
        private int line;
        private int column;

        WrappedInputStreamReader(
            InputStreamReader inner,
            SourceReference startSource) {
            this.inner = inner;
            this.startSource = startSource;
            this.line = startSource.getLine();
            this.column = startSource.getColumn();
        }

        public SourceReference getCurrentSource() {
            return new SourceReference(
                this.startSource.getPath(),
                this.line,
                this.column);
        }

        public int peek() throws java.io.IOException {
            if (peekedChar == -1) {
                peekedChar = inner.read();
            }

            return peekedChar;
        }

        public int read() throws java.io.IOException {
            int ch = peek();
            peekedChar = -1;
            if (ch == '\n') {
                this.line++;
                this.column = 1;
            } else {
                this.column++;
            }

            return ch;
        }
    }
}
