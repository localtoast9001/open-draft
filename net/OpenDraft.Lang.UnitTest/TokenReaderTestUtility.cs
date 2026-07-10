// <copyright file="TokenReaderTestUtility.cs" company="Jon Rowlett">
// Copyright (c) Jon Rowlett. All rights reserved.
// </copyright>

namespace OpenDraft.Lang.UnitTest;

using System.Runtime.CompilerServices;

/// <summary>
/// Utility methods for testing the <see cref="TokenReader"/> class.
/// </summary>
internal static class TokenReaderTestUtility
{
    /// <summary>
    /// Creates a <see cref="TokenReader"/> for the given input string, using the given log and source reference information.
    /// </summary>
    /// <param name="input">The input string to read tokens from.</param>
    /// <param name="log">The log to record messages to.</param>
    /// <param name="filePath">The source file path for the input string.</param>
    /// <param name="lineNumber">The line number in the source file for the input string.</param>
    /// <returns>A <see cref="TokenReader"/> instance for the given input string.</returns>
    public static TokenReader CreateTokenReader(
        string input,
        TestMessageLog log,
        [CallerFilePath] string filePath = "",
        [CallerLineNumber] int lineNumber = 0)
    {
        return new TokenReader(
            new StringReader(input),
            new SourceReference(filePath, lineNumber),
            log.Log);
    }

    /// <summary>
    /// Creates a <see cref="TokenReader"/> for the given input string, using a new log and source reference information.
    /// </summary>
    /// <param name="expectedValue">The expected value of the single token.</param>
    /// <param name="input">The input string to read tokens from.</param>
    /// <remarks>
    /// This method asserts that the input string produces a single token with the expected value and that the token reader is clean afterwards.
    /// </remarks>
    public static void SingleTokenCleanTest(
        string expectedValue,
        string input)
    {
        var log = new TestMessageLog();

        TokenReader reader = CreateTokenReader(input, log);
        var token = reader.Read();
        Assert.IsNotNull(token);
        Assert.IsInstanceOfType<StringLiteralToken>(token);
        Assert.AreEqual(expectedValue, ((StringLiteralToken)token).Value);

        Assert.IsNull(reader.Read());
        log.AssertClean();
    }

    /// <summary>
    /// Creates a <see cref="TokenReader"/> for the given input string, using a new log and source reference information.
    /// </summary>
    /// <param name="expectedValue">The expected value of the single token.</param>
    /// <param name="input">The input string to read tokens from.</param>
    /// <param name="unit">The expected unit of the numeric literal, if any.</param>
    /// <remarks>
    /// This method asserts that the input string produces a single token with the expected value and that the token reader is clean afterwards.
    /// </remarks>
    public static void SingleTokenCleanTest(
        long expectedValue,
        string input,
        string? unit = null)
    {
        var log = new TestMessageLog();

        TokenReader reader = CreateTokenReader(input, log);
        var token = reader.Read();
        Assert.IsNotNull(token);
        Assert.IsInstanceOfType<NumericLiteralToken>(token);
        var numToken = (NumericLiteralToken)token;
        Assert.IsFalse(numToken.IsFloatingPoint);
        Assert.AreEqual(expectedValue, numToken.IntegerValue);
        Assert.AreEqual(unit, numToken.Unit);

        Assert.IsNull(reader.Read());
        log.AssertClean();
    }

    /// <summary>
    /// Creates a <see cref="TokenReader"/> for the given input string, using a new log and source reference information.
    /// </summary>
    /// <param name="expectedValue">The expected value of the single token.</param>
    /// <param name="input">The input string to read tokens from.</param>
    /// <param name="unit">The expected unit of the numeric literal, if any.</param>
    /// <remarks>
    /// This method asserts that the input string produces a single token with the expected value and that the token reader is clean afterwards.
    /// </remarks>
    public static void SingleTokenCleanTest(
        decimal expectedValue,
        string input,
        string? unit = null)
    {
        var log = new TestMessageLog();

        TokenReader reader = CreateTokenReader(input, log);
        var token = reader.Read();
        Assert.IsNotNull(token, input);
        Assert.IsInstanceOfType<NumericLiteralToken>(token, input);
        var numToken = (NumericLiteralToken)token;
        Assert.IsTrue(numToken.IsFloatingPoint, input);
        Assert.AreEqual(expectedValue, numToken.FloatingPointValue);
        Assert.AreEqual(unit, numToken.Unit);

        Assert.IsNull(reader.Read(), input);
        log.AssertClean();
    }
}