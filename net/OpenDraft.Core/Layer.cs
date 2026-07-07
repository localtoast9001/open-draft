// <copyright file="Layer.cs" company="Jon Rowlett">
// Copyright (c) Jon Rowlett. All rights reserved.
// </copyright>

namespace OpenDraft.Core;

/// <summary>
/// Represents a layer in a diagram.
/// </summary>
public class Layer
{
    private readonly List<Shape> shapes = new List<Shape>();

    /// <summary>
    /// Gets the shapes in the layer ordered back to front.
    /// </summary>
    public IList<Shape> Shapes => this.shapes;
}