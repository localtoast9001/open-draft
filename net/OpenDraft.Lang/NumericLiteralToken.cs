// <copyright file="NumericLiteralToken.cs" company="Jon Rowlett">
// Copyright (c) Jon Rowlett. All rights reserved.
// </copyright>

namespace OpenDraft.Lang;

/// <summary>
/// Represents a numeric literal token in the language.
/// </summary>
public class NumericLiteralToken : Token
{
    /// <summary>
    /// Initializes a new instance of the <see cref="NumericLiteralToken"/> class.
    /// </summary>
    /// <param name="source">The source reference for this token.</param>
    /// <param name="value">The integer value of the numeric literal.</param>
    /// <param name="unit">The unit of the numeric literal, if any.</param>
    public NumericLiteralToken(
        SourceReference source,
        long value,
        string? unit = null)
        : base(source)
    {
        this.IntegerValue = value;
        this.IsFloatingPoint = false;
        this.FloatingPointValue = default;
        this.Unit = unit;
    }

    /// <summary>
    /// Initializes a new instance of the <see cref="NumericLiteralToken"/> class.
    /// </summary>
    /// <param name="source">The source reference for this token.</param>
    /// <param name="value">The floating-point value of the numeric literal.</param>
    /// <param name="unit">The unit of the numeric literal, if any.</param>
    public NumericLiteralToken(
        SourceReference source,
        decimal value,
        string? unit = null)
        : base(source)
    {
        this.IntegerValue = default;
        this.IsFloatingPoint = true;
        this.FloatingPointValue = value;
        this.Unit = unit;
    }

    /// <summary>
    /// Gets a value indicating whether this numeric literal is a floating-point number.
    /// </summary>
    public bool IsFloatingPoint { get; }

    /// <summary>
    /// Gets the integer value of this numeric literal.
    /// </summary>
    public long IntegerValue { get; }

    /// <summary>
    /// Gets the floating-point value of this numeric literal.
    /// </summary>
    public decimal FloatingPointValue { get; }

    /// <summary>
    /// Gets the unit of this numeric literal, if any.
    /// </summary>
    public string? Unit { get; }
}