# Types and Object Model

The object model and type system define how the runtime represents and manipulates data. The type system can be used independently of the language.

## Overview of Types
Data is weakly-typed, meaning type checking occurs at runtime, and values can be coerced from one type to another depending on usage. 

The system supports the following kinds of types:
1. Primitive types.
1. Complex types (classes) that store multiple fields in a single record. 
1. Arrays.
1. Delegates that are used for pointers to functions. 
1. Dictionary - A collection of Name-value pairs.
1. Interfaces.
1. Enums.

### Primitive Types
The following primitive types are defined:
1. _boolean_ - `true` or `false`
2. _integer_ - a 64-bit signed integer.
3. _real_ - a 64-bit double precision floating point number.
4. _byte_ - an 8-bit byte.
5. _string_ - a string of UTF-8 characters.

### Complex Types (Classes)
Complex types follow a _has a model_ vs. an _is a model_ for member access.
Complex types can be coerced from and to either name-value pairs or vectors of values.
Geometry and model output are represented in the runtime with the same type system and can include extended data.

Instances of complex types refer to their type.  
Classes can have 0 or 1 base class and implement 0 or more interfaces.  
Classes have named members for data (fields), templates, and functions. Templates and functions support overloading, but a template cannot have the same name as a function and vice versa. Neither templates or functions can have the same name as a field.

Classes also can define static functions and templates.  

Currently, abstract classes and pure virtual templates or functions are not defined.  Alternatively, interfaces can be used to define abstract functions and templates.  

### Arrays
Arrays can be multi-dimensional and also support heterogenous values.

### Delegates
Delegates are references to functions which have zero or more captured argument bindings. It may have at most one argument binding that is unnamed for the implicit argument. The runtime is responsible for coercing arguments, including the implicit argument, when the delegate is invoked.

### Dictionary - Collection of Name-Value Pairs
A collection of name-value pairs is the same as a complex type in terms of how data is organized and accessed. It is only missing an explicit type assignment.

### Interfaces

Interfaces are collections of templates and functions that are ultimately implemented by classes. An interface can have 0 or more base interfaces which means the funal interface includes the union of all functions and templates through transitive closure of all the base interfaces.  

### Enums
Enums are represented as integer primitives. The type information for enums describes the mapping from name to value. 

## Object Model

The object model will be implementation dependent and built on corresponding runtimes, but should be based on the following abstract object model API specification. The structure of the object model is optimized around the following principles:
1. Near native representation of large arrays of primitive values.
1. Low overhead of accessing vectors or multi-dimensional geometry by either ordinal or name.

### Object

This is the core of the object model. An object represents any instance of data, whether that is a primitive, complex object, array, delegate, or interface.  Objects are immutable once created, and their lifetime is controlled by the components and other objects that reference them.  How this is accomplished is implementation specific, where Java and .Net intrinsically support garbage collection, where C/C++ would need an explicit way of managing lifetime, for example with `std::shared_ptr<>`.

All objects have a type reference and one or more dimensions. Different implementations may decide to implement these as virtual methods or structured fields in the native type system. The type determines the layout of the object and how members are accessed.  All data is accessed by ordinal/index. The type is used to map names to ordinal in the object.

For primitives, the implementation is responsible for how data is encapsulated within the object and accessed using methods to convert the object to a corresponding native representation. 

The implementation decides how to expose runtime errors on invalid access.

### Type
The type object allows an implementation or consumer of the object model to access data stored within the object, perform appropriate data type coercion, and allows it to dispatch calls into objects.

Different implementations may either have an abstract _type_ class and have different kinds of types, like arrays or interfaces, derived from that base type, or it can use a singular type representation and use an enum to indicate its kind. Each kind of type will have different accessors and object layout described below.

The _type_ class should also expose the type's fully qualified name. How types are managed is described later in the Type System.  Implementation may implement functions to determine equality of types on the _type_ itself or provide a comparison function in the type system.  

#### Primitive Types
Each primitive type can be represented by an enum or subclass of type in the implementation.

#### Array Types
The array type has a reference to the element type and and integer for the number of dimensions in the array.  

#### Class Types
A class type offers the following:
1. A field map, binding a string name to an ordinal and a type for the field.
2. A method map, binding a method signature to a method implementation. 
3. A normalized list of interfaces the class implements. 
4. A reference to the base class type if any. 

#### Interface Types
The interface type provides:
1. A method map, binding a method signature to a method implementation.
2. A normalized list of base interfaces from which this interface derives.

#### Delegate Types
A delgate type describes method signature, including named arguments. A delegate binding type describes the layout of the delegate object and includes a reference to the delegate type.

#### Dictionary Types
Dictionary types have a map of field name to ordinal and can have an optional value type. Unlike the class, field names are sorted alphabetically. 

### Type System
The type system interface provides common services to the implementation of the runtime for registering, accessing, and performing common operations on types. The type system may manage the lifetime of all type information during the entire runtime lifecycle.

The type system should offer the following services:
1. Get type by name.
1. Get well-known primitive types. 
1. Get the array type for a given element type and the count of dimensions.
1. Create and register an interface type given its properties.
1. Create and register a class type given its properties.
1. Create or retrieve a dictionary type given names and optional value type.

### Object Projection
This is an optional memory optimization the implementation can offer. Instead of copying large amounts of data when objects are copied as part of coercion or assigning values to members of new objects, a wrapper projection implements the same core methods as the object, but refers to the original object. Values are only copied on read. This optimization can be hidden from consumers of the object model implementation.

### Method Implementations
The type system and object model should use the same facility for referencing method implementations, whether the implementation is done in an interpreter or with compiled programs. This can be accomplished with a string symbol or an index into a dispatch table. 
