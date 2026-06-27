/**
 * Copyright (c) Jon Rowlett. All rights reserved.
 * Licensed under the MIT License. See LICENSE.md in the project root for license information.
 */
package io.github.localtoast9001.opendraft.lang.test;

import io.github.localtoast9001.opendraft.lang.SourceReference;

/**
 * Basic unit tests for {@link SourceReference}.
 */
public final class SourceReferenceTest {
    private static final int LINE_FIVE = 5;
    private static final int COLUMN_TEN = 10;
    private static final int LINE_TWO = 2;
    private static final int COLUMN_THREE = 3;
    private static final int END_LINE_SEVEN = 7;
    private static final int END_COLUMN_NINE = 9;
    private static final int LINE_FOUR = 4;
    private static final int COLUMN_EIGHT = 8;

    private SourceReferenceTest() {
    }

    /**
     * Entry point for running SourceReference tests.
     *
     * @param args Unused command-line arguments.
     */
    public static void main(String[] args) {
        testConstructorWithPathOnly();
        testConstructorWithLineAndColumn();
        testConstructorWithFullCoordinates();
        testEndDefaultsWhenZero();
        testToStringFormat();
    }

    /**
     * Tests constructor that takes only path.
     */
    private static void testConstructorWithPathOnly() {
        SourceReference reference = new SourceReference("test.odl");
        assertEquals("test.odl", reference.getPath(), "Path should match input path");
        assertEquals(0, reference.getLine(), "Line should default to 0");
        assertEquals(0, reference.getColumn(), "Column should default to 0");
        assertEquals(0, reference.getEndLine(), "End line should default to 0");
        assertEquals(0, reference.getEndColumn(), "End column should default to 0");
    }

    /**
     * Tests constructor that takes path, line, and column.
     */
    private static void testConstructorWithLineAndColumn() {
        SourceReference reference = new SourceReference("test.odl", LINE_FIVE, COLUMN_TEN);
        assertEquals(LINE_FIVE, reference.getLine(), "Line should match input line");
        assertEquals(COLUMN_TEN, reference.getColumn(), "Column should match input column");
        assertEquals(LINE_FIVE, reference.getEndLine(), "End line should default to start line");
        assertEquals(COLUMN_TEN, reference.getEndColumn(), "End column should default to start column");
    }

    /**
     * Tests constructor that takes full coordinate range.
     */
    private static void testConstructorWithFullCoordinates() {
        SourceReference reference = new SourceReference(
            "test.odl",
            LINE_TWO,
            COLUMN_THREE,
            END_LINE_SEVEN,
            END_COLUMN_NINE);
        assertEquals(LINE_TWO, reference.getLine(), "Line should match input line");
        assertEquals(COLUMN_THREE, reference.getColumn(), "Column should match input column");
        assertEquals(END_LINE_SEVEN, reference.getEndLine(), "End line should match input end line");
        assertEquals(END_COLUMN_NINE, reference.getEndColumn(), "End column should match input end column");
    }

    /**
     * Tests that end values default to start values when end inputs are zero.
     */
    private static void testEndDefaultsWhenZero() {
        SourceReference reference = new SourceReference("test.odl", LINE_FOUR, COLUMN_EIGHT, 0, 0);
        assertEquals(LINE_FOUR, reference.getEndLine(), "End line should default to start line");
        assertEquals(COLUMN_EIGHT, reference.getEndColumn(), "End column should default to start column");
    }

    /**
     * Tests string formatting output.
     */
    private static void testToStringFormat() {
        SourceReference reference = new SourceReference("test.odl", 1, LINE_TWO, COLUMN_THREE, LINE_FOUR);
        assertEquals("test.odl:1:2-3:4", reference.toString(), "toString format should match expected shape");
    }

    /**
     * Asserts equality for object values.
     *
     * @param expected Expected value.
     * @param actual Actual value.
     * @param message Assertion message.
     */
    private static void assertEquals(Object expected, Object actual, String message) {
        if (expected == null ? actual != null : !expected.equals(actual)) {
            throw new AssertionError(message + ". Expected: " + expected + ", Actual: " + actual);
        }
    }

    /**
     * Asserts equality for integer values.
     *
     * @param expected Expected value.
     * @param actual Actual value.
     * @param message Assertion message.
     */
    private static void assertEquals(int expected, int actual, String message) {
        if (expected != actual) {
            throw new AssertionError(message + ". Expected: " + expected + ", Actual: " + actual);
        }
    }
}
