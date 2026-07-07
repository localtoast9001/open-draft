// <copyright file="PathShape.cs" company="Jon Rowlett">
// Copyright (c) Jon Rowlett. All rights reserved.
// </copyright>

namespace OpenDraft.Core;

/// <summary>
/// A shape that represents a path in a layer.
/// </summary>
public class PathShape : Shape
{
    /// <summary>
    /// Initializes a new instance of the <see cref="PathShape"/> class.
    /// </summary>
    /// <param name="components">The components of the path.</param>
    /// <param name="closed">Indicates whether the path is closed.</param>
    public PathShape(IEnumerable<PathComponent> components, bool closed)
    {
        this.Components = components?.ToList() ?? throw new ArgumentNullException(nameof(components));
        this.IsClosed = closed;
    }

    /// <summary>
    /// Gets the components of the path in order.
    /// </summary>
    public IList<PathComponent> Components { get; }

    /// <summary>
    /// Gets a value indicating whether the path is closed.
    /// </summary>
    public bool IsClosed { get; }
}