// <copyright file="TokenReaderNumericLiteralTests.cs" company="Jon Rowlett">
// Copyright (c) Jon Rowlett. All rights reserved.
// </copyright>

namespace OpenDraft.Lang.UnitTest;

/// <summary>
/// Unit tests for the <see cref="TokenReader"/> class that exercise reading numeric literals.
/// </summary>
[TestClass]
public class TokenReaderNumericLiteralTests
{
    /// <summary>
    /// Tests that the numeric literal "0" is read correctly.
    /// </summary>
    [TestMethod]
    public void TestIntegerZero()
    {
        TokenReaderTestUtility.SingleTokenCleanTest(
            expectedValue: 0,
            input: "0");
    }

    /// <summary>
    /// Tests that the numeric literal "123" is read correctly.
    /// </summary>
    [TestMethod]
    public void TestBasicInteger()
    {
        TokenReaderTestUtility.SingleTokenCleanTest(
            expectedValue: 123,
            input: "123");
    }

    /// <summary>
    /// Tests that the numeric literal "0.0" is read correctly.
    /// </summary>
    [TestMethod]
    public void TestFloatingPointZero()
    {
        TokenReaderTestUtility.SingleTokenCleanTest(
            expectedValue: 0.0m,
            input: "0.0");
    }

    /// <summary>
    /// Tests that the numeric literal ".0123" is read correctly.
    /// </summary>
    [TestMethod]
    public void TestStartingDecimalPoint()
    {
        TokenReaderTestUtility.SingleTokenCleanTest(
            expectedValue: 0.0123m,
            input: ".0123");
    }

    /// <summary>
    /// Tests that the numeric literal "123.456" is read correctly.
    /// </summary>
    [TestMethod]
    public void TestFloatingPointNoExponent()
    {
        TokenReaderTestUtility.SingleTokenCleanTest(
            expectedValue: 123.456m,
            input: "123.456");
    }

    /// <summary>
    /// Tests that the numeric literal "123.456e7" is read correctly.
    /// </summary>
    [TestMethod]
    public void TestFullFloatingPoint()
    {
        TokenReaderTestUtility.SingleTokenCleanTest(
            expectedValue: 123.456e7m,
            input: "123.456e7");
    }

    /// <summary>
    /// Tests that the numeric literal "123.456E7" is read correctly.
    /// </summary>
    [TestMethod]
    public void TestFullFloatingPointWithUppercaseE()
    {
        TokenReaderTestUtility.SingleTokenCleanTest(
            expectedValue: 123.456e7m,
            input: "123.456E7");
    }

    /// <summary>
    /// Tests that the numeric literal "123.456e-7" is read correctly.
    /// </summary>
    [TestMethod]
    public void TestFullFloatingPointWithNegativeExponent()
    {
        TokenReaderTestUtility.SingleTokenCleanTest(
            expectedValue: 123.456e-7m,
            input: "123.456e-7");
    }

    /// <summary>
    /// Tests that the numeric literal "123e4" is read correctly.
    /// </summary>
    [TestMethod]
    public void TestIntegerWithExponentLowercaseE()
    {
        TokenReaderTestUtility.SingleTokenCleanTest(
            expectedValue: 123e4m,
            input: "123e4");
    }

    /// <summary>
    /// Tests that the numeric literal "123E4" is read correctly.
    /// </summary>
    [TestMethod]
    public void TestIntegerWithExponentUppercaseE()
    {
        TokenReaderTestUtility.SingleTokenCleanTest(
            expectedValue: 123e4m,
            input: "123E4");
    }

    /// <summary>
    /// Tests that the numeric literal "123e+4" is read correctly.
    /// </summary>
    [TestMethod]
    public void TestIntegerWithPositiveExponent()
    {
        TokenReaderTestUtility.SingleTokenCleanTest(
            expectedValue: 123e4m,
            input: "123e+4");
    }

    /// <summary>
    /// Tests that the numeric literal "123mm" with a unit is read correctly.
    /// </summary>
    [TestMethod]
    public void TestIntegerWithUnits()
    {
        TokenReaderTestUtility.SingleTokenCleanTest(
            expectedValue: 123,
            input: "123mm",
            unit: "mm");

        TokenReaderTestUtility.SingleTokenCleanTest(
            expectedValue: 60,
            input: "60°",
            unit: "°");

        TokenReaderTestUtility.SingleTokenCleanTest(
            expectedValue: 60,
            input: "60_ft",
            unit: "ft");
    }

    /// <summary>
    /// Tests that the numeric literal "123.456\"" with a unit is read correctly.
    /// </summary>
    [TestMethod]
    public void TestDecimalWithUnits()
    {
        TokenReaderTestUtility.SingleTokenCleanTest(
            expectedValue: 123.456m,
            input: "123.456\"",
            unit: "\"");

        TokenReaderTestUtility.SingleTokenCleanTest(
            expectedValue: 22.5m,
            input: "22.5°",
            unit: "°");

        TokenReaderTestUtility.SingleTokenCleanTest(
            expectedValue: 123.456e-3m,
            input: "123.456e-3_r",
            unit: "r");

        TokenReaderTestUtility.SingleTokenCleanTest(
            expectedValue: 3.14m,
            input: "3.14㎭",
            unit: "㎭");
    }

    /// <summary>
    /// Tests that hexadecimal numeric literals are read correctly.
    /// </summary>
    [TestMethod]
    public void TestHexNumber()
    {
        TokenReaderTestUtility.SingleTokenCleanTest(
            expectedValue: 0x1a3f,
            input: "0x1a3f");

        TokenReaderTestUtility.SingleTokenCleanTest(
            expectedValue: 0X1A3F,
            input: "0X1A3F");
    }

    /// <summary>
    /// Tests that hexadecimal numeric literals with units are read correctly.
    /// </summary>
    [TestMethod]
    public void TestHexNumberWithUnits()
    {
        TokenReaderTestUtility.SingleTokenCleanTest(
            expectedValue: 0x1a3f,
            input: "0x1a3fmm",
            unit: "mm");
    }

    /// <summary>
    /// Tests that octal numeric literals are read correctly.
    /// </summary>
    [TestMethod]
    public void TestOctalNumber()
    {
        TokenReaderTestUtility.SingleTokenCleanTest(
            expectedValue: Convert.ToInt32("123", 8),
            input: "0o123");

        TokenReaderTestUtility.SingleTokenCleanTest(
            expectedValue: Convert.ToInt32("123", 8),
            input: "0O123");
    }

    /// <summary>
    /// Tests that binary numeric literals are read correctly.
    /// </summary>
    [TestMethod]
    public void TestBinaryNumber()
    {
        TokenReaderTestUtility.SingleTokenCleanTest(
            expectedValue: 0b1010,
            input: "0b1010");

        TokenReaderTestUtility.SingleTokenCleanTest(
            expectedValue: 0B1010,
            input: "0B1010");
    }

    /// <summary>
    /// Tests various corner cases for numeric literals.
    /// </summary>
    [TestMethod]
    public void TestCornerCases()
    {
        var testCases = new (string Input, decimal Expected)[]
        {
            ("0.0", 0m),
            ("0e0", 0m),
            ("0.0e0", 0m),
            ("1e-1", 0.1m),
            ("1e-2", 0.01m),
            ("1e-3", 0.001m),
            ("1e-4", 0.0001m),
            ("1e-5", 0.00001m),
            ("1e-6", 0.000001m),
            ("1e-7", 0.0000001m),
            ("1.e+1", 1e1m),
            ("1.", 1m),
        };

        foreach (var (input, expected) in testCases)
        {
            TokenReaderTestUtility.SingleTokenCleanTest(
                expectedValue: expected,
                input: input);
        }
    }

    /// <summary>
    /// Tests that the numeric literal "123e" fails with an error.
    /// </summary>
    [TestMethod]
    public void TestEmptyExponentFailsWithError()
    {
        ExponentErrorTest("123e");
    }

    /// <summary>
    /// Tests that the numeric literal "123e-" fails with an error.
    /// </summary>
    [TestMethod]
    public void TestEmptyNegativeExponentFailsWithError()
    {
        ExponentErrorTest("123e-");
    }

    /// <summary>
    /// Tests that the numeric literal "123e+" fails with an error.
    /// </summary>
    [TestMethod]
    public void TestEmptyPositiveExponentFailsWithError()
    {
        ExponentErrorTest("123e+");
    }

    /// <summary>
    /// Tests that a numeric literal with an invalid unit fails with an error.
    /// </summary>
    [TestMethod]
    public void TestInvalidUnit()
    {
        var log = new TestMessageLog();
        var reader = TokenReaderTestUtility.CreateTokenReader(
            input: "123_",
            log: log);
        var actual = reader.Read();
        Assert.IsNull(actual);
        Assert.HasCount(1, log.Messages);
        var message = log.Messages[0];
        Assert.AreEqual("Invalid unit specifier ''.", message.Text);
    }

    private static void ExponentErrorTest(string input)
    {
        var log = new TestMessageLog();
        var reader = TokenReaderTestUtility.CreateTokenReader(
            input: input,
            log: log);
        var actual = reader.Read();
        Assert.IsNull(actual);
        Assert.HasCount(1, log.Messages);
        var message = log.Messages[0];
        Assert.AreEqual("Expected decimal value for exponent in numeric literal.", message.Text);
    }
}
