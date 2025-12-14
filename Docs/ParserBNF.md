# Parser BNF

this is to show conceptionally how the parser works, demonstrate how different data types are defined, the valid ways of assignment, give curious programmers insight on how to make there own parser and provide documentation to others and myself for future updates on the language. This document will cover every kind of valid statement someone can enter using the basic data types and commands provided by the **Fizz** language and will be updated with every new addition to the language.

## Terminals

```
LEFT_PAREN
RIGHT_PAREN
LEFT_BRACE
RIGHT_BRACE
COMMA
DOT
MINUS
PLUS
SEMICOLON
SLASH
STAR
ADDRESS
QUOTATION
STRING
BOOL
CHAR
INT
FLOAT
ARRAY
DOUBLE
CONSTANT
NOT
EQUAL
GREATER
LESS
AND
CLASS
ELSE
ELIF
FALSE
FOR
IF
NULL_EMPTY
OR
RETURN
WHILE
VOID
```

## Non Terminals

```
Program
Function 
Statement
Expression 
Number
```

## Full BNF

```
<Program> ::= <Function> | <Statement>
```