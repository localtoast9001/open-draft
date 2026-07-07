// <copyright file="Diagram.cs" company="Jon Rowlett">
// Copyright (c) Jon Rowlett. All rights reserved.
// </copyright>

namespace OpenDraft.Core
{
    /// <summary>
    /// Represents a diagram, the root of the OpenDraft model.
    /// </summary>
    public class Diagram
    {
        private readonly List<Layer> layers = new List<Layer>();

        /// <summary>
        /// Gets the layers in the diagram, ordered back to front.
        /// </summary>
        public IList<Layer> Layers => this.layers;
    }
}