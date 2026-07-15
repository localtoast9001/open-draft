# Language (ODLang)

## Lexical Reference
ODLang files are expected to be UTF-8 text files. A lexer scans the file to produce a sequence of tokens described below. Comments and whitespace can appear between any token.

Whitespace characters ( `\x20` (space), `\t`, `\r`, `\n`) are not significant and skipped over by the lexer unless inside a string literal.

Comments follow the C/C++ convention.  
A single-line comment starts with `//` and all characters are part of the comment until the next line.
A block comment starts with `/*` and includes all characters until the sequence `*/` is encountered or the end of the file.

A token can be one of the following types:
* identifier
* numeric literal
* string literal
* keyword
* symbol

### Identifier
An identifier is a sequence of characters starting with `_`, `A`-`Z`, or `a`-`z` and continuing with `_`, `A`-`Z`, `a`-`z`, or `0`-`9` until reaching a character that does not match the pattern or the end of the file.

### Numeric Literal
A numeric literal is a sequence of `0`-`9` followed by a `.`, an optional sequence of `0`-`9`, and an optional exponent. A numeric literal also can start with `.` followed immediately by a sequence of `0`-`9` and an optional exponent. 

The exponent starts with `e` or `E` then an optional sign `-` or `+`, then one or more digits `0`-`9`.

Integer numeric literal can also be specified in hexidecimal, octal, or binary.

A hexadecimal literal starts with `0x` or `0X` followed by a sequence of one or more digits of `0`-`9`, `A`-`F`, or `a`-`f`.

An octal literal starts with `0o` or `0O` followed by a sequence of one or more digits of `0`-`7`.

A binary literal starts with `0b` or `0B` followed by a sequence of `0`-`1`.

#### Units
Numeric literals can also be qualifed with a unit of measurement. The unit syntax is as follows:  
_unit_ ::= *unit_start_char* ( *unit_char* )*  
*unit_start_char* ::= `'` | `"` | `°` (U+00B0) | `㎭` (U+33AD) | `a` - `z` | `A` - `Z`  
*unit_char* ::= `a`-`z` | `A`-`Z` | `0`-`9` | `_`
The unit immediately follows the numeric character sequence without spaces. To disambiguate hex digits and the exponent, the `_` delimiter can be used between the number and the unit.

Unit mechanics are discussed separately.  
Examples:  
* `5m` - 5 metres.  
* `5in` - 5 inches.
* `5"` - 5 inches.
* `5ft` - 5 feet.
* `5'` - 5 feet.
* `60°` - 60 degrees.
* `45deg` - 45 degrees.
* `1.0e-03rad` - 0.001 radians.
* `3.14㎭` - 3.14 radians.
* `0x1c_cm` - 0x1c (28) centimetres.
* `0x1ccm` - 0x1cc (460) metres.
* `0x5_ft` - 5 feet.

### String Literal
A string literal starts with `"` and ends with `"`. Unterminated strings generate an error condition during lexical analysis. The sequence of characters inside the string can be one of the following:
1. Any literal UTF-8 character sequence except `"`, `\`, newline (U+000A), or carriage return (U+000D).  
2. An escape sequence described below.  

Similar C or FORTRAN, there are supported escape sequences starting with a `\`. The following are recognized escape sequences:
* `\\` - a single `\` character.
* `\"` - a single `"` character.
* `\a` - audible bell character. (U+0007).
* `\b` - backspace character. (U+0008).
* `\t` - a tab character. (U+0009).  
* `\n` - a newline character. (U+000A).
* `\v` - verticle tab. (U+000B).
* `\f` - form feed. (U+000C).
* `\r` - a carriage return character. (U+000D).
* `\x`{N:1-2} - a one or 2 digit hexadecimal code for a UTF-8 encoded character. 

### Keywords
These are reserved words that cannot be used as identifiers.  

`break` - break statement.  
`class` - defines a new class type.  
`continue` - continue statement.  
`debug` - debug trace statement.  
`else` - else statement.  
`enum` - defines a new enumeration type.  
`error` - error trace statement.  
`false` - literal for a false boolean value.  
`for` - for loop statement.  
`function` - defines a function.  
`if` - if statement.  
`import` - imports a module.  
`in` - Used to determine if a value is within a set or range.
`info` - info trace statement.
`interface` - defines an interface.     
`namespace` - namespace declaration.  
`null` - null literal.  
`return` - return statement.  
`static` - static member modifier.  
`template` - defines a template.  
`throw` - throw statement.  
`true` - literal for a true boolean value.  
`verbose` - verbose trace statement.  
`warn` - warn trace statement.  

### Symbols
These sequences of symbols have distinct meaning as tokens.  
`~` - bitwise inverse unary operator.  
`%` - modulus operator.  
`&` - bitwise AND binary operator.  
`&&` - logical AND operator.  
`*` - multiplication operator.  
`(` - context dependent.  
`)` - context dependent.  
`-` - subtraction binary operator or unary negative operator.  
`+` - addition binary operator or unary positive operator.  
`=` - assignment operator.  
`==` - equals operator.  
`!=` - not equals operator.  
`[` - array start.  
`]` - array end.  
`{` - block start.  
`}` - block end.  
`/` - division operator.  
`|` - bitwise OR operator.  
`||` - logical OR operator.   
`:` - context specific.  
`;` - statement end.  
`,` - context specific.  
`<` - less than operator.  
`<=` - less than or equal to operator.  
`>` - greater than operator.  
`>=` - greater than or equal to operator.  
`<<` - shift left operator.  
`>>` - shift right operator.  
`?` - start of a conditional operator.  
`??` - reserved (null/default coalescing operator).  
`.` - scoping operator.  
`..` - range operator.  
`!` - logical inverse.  

## Grammar Reference

_program_ ::= *import_statement* * *program_element* *  

*import_statement* ::= `import` *string_literal* `;`  

*program_element* ::=   
    *class_definition* |  
    *enum_definition* |  
    *interface_definition* |  
    *namespace_definition* |  
    *function_definition* |  
    *template_definition* |  
    *core_statement*
    
*namespace_definition* ::= `namespace` _identifier_ `{` *program_element* * `}`  

### Enum Definition
*enum_definition* ::=  `enum` _identifier_ `{` *enum_val* ( `,` *enum_val* )* `}`  
*enum_val* ::= _identifier_ [ `=` *numeric_literal* ]  

### Class Definition
*class_definition* ::= `class` _identifier_ [ `:` *base_and_interface_list* ]  `{` *class_member* * `}`  
*base_and_interface_list* ::= *type_reference* ( `,` *type_reference* )*  
*class_member* ::= [ `static` ] ( *class_variable* | *class_function* | *class_template* )  
*class_variable* ::= [ *type_reference* ] _identifier_ [ `=` _expression_ ] `;`  
*class_function* ::= `function` _identifier_ *parameters_declaration* *block_statement*  
*class_template* ::= `template` _identifier_ *parameters_declaration* *block_statement*  

### Interface Definition

*interface_definition* ::= `interface` _identifier_ [ `:` *base_and_interface_list* ] `{` *interface_member* * `}`  
*interface_member* ::= *function_declaration* | *template_declaration*
*function_declaration* ::= `function` _identifier_ *parameters_declaration* `;`  
*template_declaration* ::= `template` _identifier_ *parameters_declaration* `;`  

### Function and Template Definitions

*function_definition* ::= `function` _identifier_ *parameters_declaration* *block_statement*

*template_definition* ::= `template` _identifier_ *parameters_declaration* *block_statement*  

*parameters_declaration* ::= `(` _e_ | ( *parameter_declaration* ( `,` *parameter_declaration* )* ) `)`  
*parameter_declaration* ::= [ *type_reference* ] _identifier_ [ `=` _expression_ ]  

*variable_definition* ::= [ *type_reference* ] _identifier_ `=` _expression_ `;`  

### Statements
_statement_ ::= *block_statement* | *core_statement*  
*block_statement* ::= `{` *core_statement* * `}`  
*core_statement* ::=  
    *if_statement* |  
    *for_statement* |  
    *break_statement* |  
    *continue_statement* |   
    *return_statement* |  
    *assign_statement* |  
    *call_statement* |  
    *throw_statement* |  
    *trace_statement* |  
    `;`   

*if_statement* ::= `if` `(` *expression* `)` _statement_ [ `else` _statement_ ]  
*for_statement* ::= `for` `(` *for_condition* [ `;` *for_condition* ]* `)` _statement_  
*for_condition* ::= [ *type_reference* ] _identifier_ [ `,` _identifier_ ]* `:` _expression_
*break_statement* ::= `break` `;` 
*continue_statement* ::= `continue` `;` 
*return_statement* ::= `return` [ _expression_ ] `;`   
*assign_statement* ::= [ *type_reference* ] _identifier_ `=` _expression_ `;`  
*call_statement* ::= *reference_expression* `(` *argument_list* `)` `;` 
*throw_statement* ::= `throw` _expression_ `;` 
*trace_statement* ::= ( `error` | `warn` | `info` | `verbose` | `debug` ) _expression_  `;`

### Expressions
*type_reference* ::= _identifier_ [ `.` _identifier_ ]*
*expression* ::=  *logical_or_expression* [ `?` *expression* `:` *expression* ]  
*logical_or_expression* ::= [ *logical_or_expression* `||` ] *logical_and_expression*  
*logical_and_expression* ::= [ *logical_and_expression* `&&` ] *bitwise_or_expression*  
*bitwise_or_expression* ::= [ *bitwise_or_expression* `|` ] *bitwise_xor_expression*  
*bitwise_xor_expression* :: = [ *bitwise_xor_expression* `^` ] *bitwise_and_expression*
*bitwise_and_expression* ::= [ *bitwise_and_expression* `&` ] *equality_expression*  
*equality_expression* ::= [ *equality_expression* ( `==` | `!=` ) ] *relational_expression*  
*relational_expression* ::= [ *relational_expression* ( `<` | `>` | `<=` | `>=` | `in` ) ] *shift_expression*  
*shift_expression* ::= [ *shift_expression* ( `<<` | `>>` ) ] *add_expression*  
*add_expression* ::= [ *add_expression* ( `+` | `-` ) ] *mul_expression*  
*mul_expression* ::= [ *mul_expression* ( `*` | `/` | `%` )] *range_expression*  
*range_expression* ::= *unary_expression* [ `..` *unary_expression* ]  
*unary_expression* ::= ( ( `-` | `+` | `!` | `~` ) *unary_expression* ) | *paren_expression* | *reference_expression* | *literal_expression* | *array_expression* | *object_expression*    
*paren_expression* ::= `(` _expression_ `)`  
*literal_expression* ::= `true` | `false` | `null` | *numeric_literal* | *string_literal*  
*array_expression* ::= `[` _e_ | ( _expression_ [ `,` _expression_ ]* ) `]`  
*object_expression* ::= `{` _e_ | ( *obj_member* [ `,` *obj_member* ]* ) `}`
*reference_expression* ::= _identifier_ | *member_reference* | *array_index* | *call_expression*  
*member_reference* ::= *reference_expression* `.` _identifier_  
*array_index* ::= *reference_expression* `[` *expression* `]`  
*call_expression* ::= *reference_expression* `(` *argument_list* `)`  
*obj_member* ::= _identifier_ `=` _expression_  
*argument_list* ::= _e_ | ( _argument_ ( `,` _argument_ )* )  
*argument* ::= [ _identifier_ `=` ] _expression_  

## Messages
These are the messages, with specific codes and severity, that should be produced by any compiler or interpreter implementation of the language.  

Severity can be one of the following:
1. **error** - Indicates the component processing the input cannot infer or otherwise produce valid output required by the next stage.
2. **warning** - Indicates a condition encountered where syntax may be undesired but still constitutes a valid program.  
3. **info** - Indicates an informational message.  

Each messages has a default severity. Implementations may allow the user to treat warnings as errors or modify the severity of each message.  

Codes start with `ODL` followed by a 4 digit decimal code. Ranges of codes are reserved for specific areas of implementation according to responsibility.

0000        - Unused.  
0001-0999   - Internal or implementation specific messsages.  
1000-1999   - Lexer messages.  
2000-2999   - Parser messages.  
3000-3999   - Syntax analysis messages.  

### Lexer Messages (ODL1000-ODL1999)
ODL1000 - **ERROR** - Unterminated string literal.  
ODL1001 - **ERROR** - Unrecognized character.  
ODL1002 - **ERROR** - Unterminated multi-line comment.  
ODL1003 - **ERROR** - Unknown escape sequence in string literal.
ODL1004 - **ERROR** - Invalid hex value argument to escape sequence in string literal.  
ODL1005 - **ERROR** - Expected decimal value for exponent in numeric literal.  
ODL1006 - **ERROR** - Invalid unit specifier in numeric literal.  
ODL1007 - **ERROR** - Invalid number after radix specifier.  

### Parser Messages (ODL2000-ODL2999)
ODL2000 - **ERROR** - Unexpected end of file.  
ODL2001 - **ERROR** - Keyword {keyword} expected.  
ODL2002 - **ERROR** - Symbol {symbol} expected.  
ODL2003 - **ERROR** - Identifier expected.  
ODL2004 - **ERROR** - String literal expected.  
ODL2005 - **ERROR** - Numeric literal expected.  
ODL2006 - **ERROR** - Integer literal expected.  
ODL2007 - **ERROR** - Variable name expected after type reference.  
ODL2100 - **ERROR** - Unexpected token.  
