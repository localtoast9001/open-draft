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

### String Literal
A string literal starts with `"` and ends with `"`. Unterminated strings generate an error condition.  

Similar C or FORTRAN, there are supported escape sequences starting with a `\`. The following are recognized escape sequences:
* `\\` - a single `\` character.
* `\"` - a single `"` character.
* `\n` - a newline character. ASCII/UTF code 0x10.
* `\r` - a carriage return character. ASCII/UTF code 0x13.
* `\t` - a tab character. TODO: put the code in.
* `\x`NN - a hexadecimal code for a UTF-8 encoded character. 


### Keywords
These are reserved words that cannot be used as identifiers.  

`class` - defines a new class type.  
`enum` - defines a new enumeration type.  
`false` - literal for a false boolean value.  
`function` - defines a function.  
`interface` - defines an interface.     
`template` - defines a template.  
`true` - literal for a true boolean value.

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
`[` - array start.  
`]` - array end.  
`{` - block start.  
`}` - block end.  
`/` - division operator.  
`|` - bitwise OR operator.  
`||` - logical OR operator.   
`:` - context specific.  
`::` - scoping operator.  
`;` - statement end.  
`,` - context specific.  
`<` - less than operator.  
`<=` - less than or equal to operator.  
`>` - greater than operator.  
`>=` - greater than or equal to operator.  
`?` - start of a conditional operator.  
`??` - reserved.  

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
    *variable_definition*
    
*namespace_definition* ::= `namespace` _identifier_ `{` *program_element* * `}`

### Enum Definition
*enum_definition* ::=  `enum` _identifier_ `{` *enum_val* ( `,` *enum_val* )* `}`  
*enum_val* ::= _identifier_ [ `=` *numeric_literal* ]  

### Class Definition
*class_definition* ::= `class` _identifier_ [ `:` *base_and_interface_list* ]  
*base_and_interface_list* ::= *type_reference* ( `,` *type_reference* )*

### Interface Definition

*interface_definition* ::= `interface` _identifier_ [ `:` *base_and_interface_list* ] `{` ( *function_declaration* | *template_declaration* )* `}`  
*function_declaration* ::= `function` _identifier_ *parameters_declaration* `;`  
*template_declaration* ::= `template` _identifier_ *parameters_declaration* `;`  

### Function and Template Definitions

*function_definition* ::= `function` _identifier_ *parameters_declaration* *block_statement*

*template_definition* ::= `template` _identifier_ *parameters_declaration* *block_statement*

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
*for_statement* ::= `for` `(` *for_condition* [ `,` *for_condition* ]* `)` _statement_  
*for_condition* ::= [ *type_reference* ] _identifier_ [ `,` _identifier_ ]* `:` _expression_
*break_statement* ::= `break` `;`  
*continue_statement* ::= `continue` `;`  
*return_statement* ::= `return` _expression_ `;`  
*assign_statement* ::= [ *type_reference* ] _identifier_ `=` _expression_ `;`    
*call_statement* ::= *reference_expression* `(` *argument_list* `)` `;`  
*throw_statement* ::= `throw` _expression_ `;`  
*trace_statement* ::= ( `error` | `warn` | `info` | `verbose` | `debug` ) _expression_ `;`    

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
*literal_expression* ::= `true` | `false` | *numeric_literal* | *string_literal*  
*array_expression* ::= `[` _expression_ [ `,` _expression_ ]* `]`  
*object_expression* ::= `{` *obj_member* [ `,` *obj_member* ]* `}`
*reference_expression* ::= _identifier_ | *member_reference* | *array_index* | *call_expression*  
*member_reference* ::= *reference_expression* `.` _identifier_  
*array_index* ::= *reference_expression* `[` *expression* `]`  
*call_expression* ::= *reference_expression* `(` *argument_list* `)`  
*obj_member* ::= _identifier_ `=` _expression_  

