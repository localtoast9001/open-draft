// <copyright file="GroupShape.cs" company="Jon Rowlett">
// Copyright (c) Jon Rowlett. All rights reserved.
// </copyright>

namespace OpenDraft.Core;

/// <summary>
/// A group of shapes that can be treated as a single shape.
/// </summary>
public class GroupShape : Shape
{
    private readonly List<Shape> shapes = new List<Shape>();

    /// <summary>
    /// Gets the shapes in the group ordered back to front.
    /// </summary>
    public IList<Shape> Shapes => this.shapes;
}