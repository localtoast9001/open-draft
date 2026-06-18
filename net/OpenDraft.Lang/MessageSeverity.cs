// <copyright file="MessageSeverity.cs" company="Jon Rowlett">
// Copyright (c) Jon Rowlett. All rights reserved.
// </copyright>

namespace OpenDraft.Lang;

/// <summary>
/// Severity of a message produced by any of the language components.
/// </summary>
public enum MessageSeverity
{
    /// <summary>
    /// Represents an informational message.
    /// </summary>
    Info = 0,

    /// <summary>
    /// Represents a warning message.
    /// </summary>
    Warning,

    /// <summary>
    /// Represents an error message.
    /// </summary>
    Error,
}