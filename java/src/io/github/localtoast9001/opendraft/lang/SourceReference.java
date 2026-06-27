/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 * Licensed under the MIT License. See LICENSE.md in the project root for license information.
 */
package io.github.localtoast9001.opendraft.lang;

/**
 * Represents a reference to a location in the source code.
 */
public class SourceReference {
    private final int line;
    private final int column;
    private final int endLine;
    private final int endColumn;
    private final String path;

    /**
     * Creates a new instance of the SourceReference class.
     * @param path The path to the source file.
     * @param line The starting line of the reference.
     * @param column The starting column of the reference.
     * @param endLine The ending line of the reference.
     * @param endColumn The ending column of the reference.
     */
    public SourceReference(
        String path,
        int line,
        int column,
        int endLine,
        int endColumn) {
        this.path = path;
        this.line = line;
        this.column = column;
        this.endLine = endLine == 0 ? line : endLine;
        this.endColumn = endColumn == 0 ? column : endColumn;
        }

    /**
     * Creates a new instance of the SourceReference class with only a path.
     * @param path The path to the source file.
     */
    public SourceReference(String path) {
        this(path, 0, 0, 0, 0);
    }

    /**
     * Creates a new instance of the SourceReference class with a path and line number.
     * @param path The path to the source file.
     * @param line The line number of the reference.
     */
    public SourceReference(String path, int line) {
        this(path, line, 0, line, 0);
    }

    /**
     * Creates a new instance of the SourceReference class with a path, line number, and column number.
     * @param path The path to the source file.
     * @param line The line number of the reference.
     * @param column The column number of the reference.
     */
    public SourceReference(String path, int line, int column) {
        this(path, line, column, line, column);
    }

    /**
     * Gets the path to the source file.
     * @return The path to the source file.
     */
    public String getPath() {
        return this.path;
    }

    /**
     * Gets the starting line of the reference.
     * @return The starting line of the reference.
     */
    public int getLine() {
        return this.line;
    }

    /**
     * Gets the starting column of the reference.
     * @return The starting column of the reference.
     */
    public int getColumn() {
        return this.column;
    }

    /**
     * Gets the ending line of the reference.
     * @return The ending line of the reference.
     */
    public int getEndLine() {
        return this.endLine;
    }

    /**
     * Gets the ending column of the reference.
     * @return The ending column of the reference.
     */
    public int getEndColumn() {
        return this.endColumn;
    }

    /**
     * Returns a string representation of the SourceReference.
     * @return A string representation of the SourceReference.
     */
    @Override
    public String toString() {
        return String.format("%s:%d:%d-%d:%d", this.path, this.line, this.column, this.endLine, this.endColumn);
    }
}
