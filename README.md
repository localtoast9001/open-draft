# OpenDraft
OpenDraft is a programmer's CAD with emphasis on 2D drafting. Shapes are expressed using a programming language. Tools then interpret the language to either render or convert the final diagram to formats used by other programs.

## Impetus and Motivation
OpenSCAD works well for working with 3D shapes, but has gaps when it comes to evaluating 2D constructive geometry. Likewise, FreeCAD and LibreCAD require clicking around in a GUI which can be clunky for fine work.

## Concepts
A diagram is composed of a stack of layers with the first layer being behind all other layers, otherwise known as in the background.

Each layer is a composite of 0 or more shapes or groups of shapes ordered back to front.

A group can have both shapes and nested groups. Groups are also ordered back to front.

A shape can be one of the following:
1. a single point.
2. a sequence of line segments and curves. Curves can either be cubic splines or elliptical arcs. A shape can be either open or closed. Closed shapes can be filled.

Styles describe how the border and fill of a shape should be rendered.

Each object in the model, including the top level diagram, can have additional properties associated with it.

## Language

The design goals of the OpenDraft language (ODLang) are as follows:
1. Allow for simple expression of common shapes and coordinates to a user with experience with 3D modelling languages like OpenSCAD or POV-Ray.
1. Allow for simple expression of common filters and transformations, like beveled edges or constructive geometry to users familiar with 3D tools.
1. Allow for calculated values to be recoverable from the resulting output, like getting the point that is the result of intersecting lines, so it can be used as an input or constraint to other geometry.
1. Allow for both compilation and interpretation across multiple runtimes, like Java, .Net, or C.
1. Allow for sharable, self-contained libraries to be defined with common functions or stencils for geometry.
1. The language is weakly typed to minimize the tedium in specification of templates and functions.s

The language is a functional language organized into scopes that define **templates**. The main body of a program is also a template. Templates can take a number of arguments as input and produce multiple return values as output. 

Template bodies are organized into **statements** that perform a chain of processing to produce output.

Statements within a template can do one or multiple of the following:
1. Assign a variable or data to be explicitly returned from the current function.
1. Change evaluation context or scope.
1. Write output to the current container in the model based on the evaluation context.
1. Perform various control flow operations.
1. Emit instrumentation for debug or logging output.

**Functions** are restricted types of templates that must explicitly return output and cannot write output.

### Tranformation Hierarchy
Each statement that outputs geometry goes through an implicit transformation before being constructed in the final output model. Each template evaluation scope can define its own transformation, which forms a stack of transformations to be applied from the calling scopes. When a template returns, its transform is popped from the stack.

### Types
The language is weakly-typed, meaning type checking occurs at runtime, and values can be coerced from one type to another depending on usage. 

The system supports the following kinds of types:
1. Primitive types.
1. Complex types that store multiple fields in a single record.
1. Arrays.
1. Delegates that are used for pointers to functions.

Complex types follow a _has a model_ vs. an _is a model_ for member access.

Complex types can be coerced from and to either name-value pairs or vectors of values.

Geometry and model output can include extended data.

The following primitive types are defined:
1. _boolean_ - `true` or `false`
2. _integer_ - a 64-bit signed integer.
3. _real_ - a 64-bit double precision floating point number.
4. _byte_ - an 8-bit byte.
5. _string_ - a string of UTF-8 characters.

Arrays can be multi-dimensional and also support heterogenous values.

### Examples
* Draw a rectangle.
    ```
    rect(x=1, y=1, w=2, h=3);
    ```
* Define a smiley-face template.
    ```
    template smiley_face(x = 0, y = 0, w = 1, h = 1) {
        // set the local viewport so the upper left is -1,-1 locally but maps to x,y and the bottom right of 1,1 maps to x+w,y+h
        viewport(-1, -1, 2, 2, x, y, w, h);

        // draw the outline of the head.
        circle(r = 1);

        // draw the mouth.
        arc(r=0.5, src=[-0.5,0], dst=[0.5, 0]);

        // draw the eyes.
        point(-0.5, -0.5);
        point(0.5, 0.5);
    }
    ```
* Define a function.
    ```
    function length_sq(x, y) {
        return x * x + y * y;
    }
    ```