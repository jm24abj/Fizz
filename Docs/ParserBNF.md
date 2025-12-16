# Parser BNF

this is to show conceptionally how the parser works, demonstrate how different data types are defined, the valid ways of assignment, give curious programmers insight on how to make there own parser and provide documentation to others and myself for future updates on the language. This document will cover every kind of valid statement someone can enter using the basic data types and commands provided by the **Fizz** language and will be updated with every new addition to the language.

## Full BNF

```
<Dimension> ::= ε | [] | [] <Dimension> 
<DataType> ::= int | float | double | String | bool | char
<Keyword> ::= <DataType> | <DataType><Dimension>

<Number> ::= 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9
<LowerCase> ::= a | b | c | d | ... | z
<UpperCase> ::= A | B | C | D | ... | Z
<Letter> ::= <LowerCase> | <UpperCase>

<IdentifierPrefix> ::= <Letter> | _
<ValidIdentifierTail> ::= <Letter> | _ | <Number>
<IdentifierTail> ::= <ValidIdentifierTail><IdentifierTail> | ε
<Identifier> ::= <IdentifierPrefix><IdentifierTail>

<Operator> ::= + | - | / | * | % | and | or | not | xor | xnor
<Expression> ::= <Identifier><Operator><Expression> | <Identifier>
<Assignment> ::= <Keyword> <Identifier> = <Expression> SEMICOLON

<Arguments> ::= <Identifier> | <Arguments> COMMA <Identifier>
<Call> ::= <Identifier> LEFT_PAREN <Arguments> RIGHT_PAREN SEMICOLON

<Statement> ::=  <Assignment> | <Call> | RETURN | RETURN <Identifier>
<Body> ::= ε | <Statement> | <Statement><Body>

<Parameter> ::= <Keyword> <Identifier>
<Parameters> ::= <Parameter> | <Parameters> COMMA <Parameter>
<FunctionParameters> ::= <Parameters> | ε
<Function> ::= f <Keyword> LEFT_PAREN <FunctionParameters> RIGHT_PAREN LEFT_BRACE <Body> RIGHT_BRACE
<Procedure> ::= f void LEFT_PAREN <FunctionParameters> RIGHT_PAREN LEFT_BRACE <Body> RIGHT_BRACE
<Declaration> ::= <Function> | <Procedure> 
<Program> ::= ε | <Declaration> | <Declaration><Program>
```

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
Dimension
DataType
Keyword
IdentifierPrefix
ValidIdentifierTail
IdentifierTail
Identifier
Arguments
Call
Statement
Assignment
Parameter
Parameters
FunctionParameters
Function
Procedure
Declaration
Program
```
