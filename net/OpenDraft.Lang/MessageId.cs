// <copyright file="MessageId.cs" company="Jon Rowlett">
// Copyright (c) Jon Rowlett. All rights reserved.
// </copyright>

namespace OpenDraft.Lang;

/// <summary>
/// Represents an identifier for a message produced by any of the language components.
/// </summary>
/// <remarks>
/// This is a category code of a few capital letters followed by a 4-digit number. The category is used to group related messages together, and the code is used to identify the specific message within that category.
/// </remarks>
public struct MessageId : IEquatable<MessageId>, IComparable<MessageId>
{
    /// <summary>
    /// Initializes a new instance of the <see cref="MessageId"/> struct.
    /// </summary>
    /// <param name="category">The category of the message ID.</param>
    /// <param name="code">The code of the message ID.</param>
    /// <exception cref="ArgumentNullException">Thrown if <paramref name="category"/> is null.</exception>
    public MessageId(
        string category,
        int code)
    {
        this.Category = category ?? throw new ArgumentNullException(nameof(category));
        this.Code = code;
    }

    /// <summary>
    /// Gets the category of this message ID.
    /// </summary>
    public string Category { get; }

    /// <summary>
    /// Gets the code of this message ID.
    /// </summary>
    public int Code { get; }

    /// <summary>
    /// Determines whether two <see cref="MessageId"/> instances are equal.
    /// </summary>
    /// <param name="left">The first <see cref="MessageId"/> to compare.</param>
    /// <param name="right">The second <see cref="MessageId"/> to compare.</param>
    /// <returns><c>true</c> if the two <see cref="MessageId"/> instances are equal; otherwise, <c>false</c>.</returns>
    public static bool operator ==(MessageId left, MessageId right) => left.Equals(right);

    /// <summary>
    /// Determines whether two <see cref="MessageId"/> instances are not equal.
    /// </summary>
    /// <param name="left">The first <see cref="MessageId"/> to compare.</param>
    /// <param name="right">The second <see cref="MessageId"/> to compare.</param>
    /// <returns><c>true</c> if the two <see cref="MessageId"/> instances are not equal; otherwise, <c>false</c>.</returns>
    public static bool operator !=(MessageId left, MessageId right) => !left.Equals(right);

    /// <summary>
    /// Determines whether one <see cref="MessageId"/> is less than another.
    /// </summary>
    /// <param name="left">The first <see cref="MessageId"/> to compare.</param>
    /// <param name="right">The second <see cref="MessageId"/> to compare.</param>
    /// <returns><c>true</c> if the first <see cref="MessageId"/> is less than the second; otherwise, <c>false</c>.</returns>
    public static bool operator <(MessageId left, MessageId right) => left.CompareTo(right) < 0;

    /// <summary>
    /// Determines whether one <see cref="MessageId"/> is less than or equal to another.
    /// </summary>
    /// <param name="left">The first <see cref="MessageId"/> to compare.</param>
    /// <param name="right">The second <see cref="MessageId"/> to compare.</param>
    /// <returns><c>true</c> if the first <see cref="MessageId"/> is less than or equal to the second; otherwise, <c>false</c>.</returns>
    public static bool operator <=(MessageId left, MessageId right) => left.CompareTo(right) <= 0;

    /// <summary>
    /// Determines whether one <see cref="MessageId"/> is greater than another.
    /// </summary>
    /// <param name="left">The first <see cref="MessageId"/> to compare.</param>
    /// <param name="right">The second <see cref="MessageId"/> to compare.</param>
    /// <returns><c>true</c> if the first <see cref="MessageId"/> is greater than the second; otherwise, <c>false</c>.</returns>
    public static bool operator >(MessageId left, MessageId right) => left.CompareTo(right) > 0;

    /// <summary>
    /// Determines whether one <see cref="MessageId"/> is greater than or equal to another.
    /// </summary>
    /// <param name="left">The first <see cref="MessageId"/> to compare.</param>
    /// <param name="right">The second <see cref="MessageId"/> to compare.</param>
    /// <returns><c>true</c> if the first <see cref="MessageId"/> is greater than or equal to the second; otherwise, <c>false</c>.</returns>
    public static bool operator >=(MessageId left, MessageId right) => left.CompareTo(right) >= 0;

    /// <inheritdoc/>
    public override string ToString()
    {
        return $"{this.Category}{this.Code:D4}";
    }

    /// <inheritdoc/>
    public override int GetHashCode()
    {
        return this.Code.GetHashCode() ^ this.Category.GetHashCode();
    }

    /// <inheritdoc/>
    public override bool Equals(object? obj)
    {
        return obj is MessageId other && this.Equals(other);
    }

    /// <inheritdoc/>
    public bool Equals(MessageId other)
    {
        return string.Equals(this.Category, other.Category, StringComparison.Ordinal) &&
            this.Code == other.Code;
    }

    /// <inheritdoc/>
    public int CompareTo(MessageId other)
    {
        int categoryComparison = string.Compare(this.Category, other.Category, StringComparison.Ordinal);
        if (categoryComparison != 0)
        {
            return categoryComparison;
        }

        return this.Code.CompareTo(other.Code);
    }
}