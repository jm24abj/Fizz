# The Fizz Language
***Developed by Jack Milner***
\
\
[!["Buy Me A Coffee"](https://www.buymeacoffee.com/assets/img/custom_images/orange_img.png)](https://buymeacoffee.com/jackmilner)

## Table of contents


* [Overview](https://github.com/jm24abj/Fizz/edit/main/Docs/README.md)
  * [Prerequisites](#prerequisites)
  * [Summary](#summary)
  * [Data-Types](#data-types)
  * [Syntax](#syntax)
* [Lexer](https://github.com/jm24abj/Fizz/blob/main/Docs/ParserBNF.md)
* [Parser](https://github.com/jm24abj/Fizz/blob/main/Docs/ParserBNF.md)
  * [Terminals](https://github.com/jm24abj/Fizz/blob/main/Docs/ParserBNF.md#full-bnf)
  * [Non Terminals](https://github.com/jm24abj/Fizz/blob/main/Docs/ParserBNF.md#non-terminals)
  * [Full BNF](https://github.com/jm24abj/Fizz/blob/main/Docs/ParserBNF.md#terminals)
* [Abstract Syntax Tree](https://github.com/jm24abj/Fizz/blob/main/Docs/ParserBNF.md)
* [Parser](https://github.com/jm24abj/Fizz/blob/main/Docs/ParserBNF.md)

## Prerequisites
This is my own programming language written to reduce time typing and created to learn about the creation of languages and compilers for my own personal growth as a computer scientist. The program is written in **C++** and contains a **Lexer**, **Abstract syntax tree**, **Parser** and a module for converting IR code to an object file. This project also makes use of **LLVM** which is the software used to make the C compiler CLANG. 

### Summary
My language is...
* A compiled language written for simplicity and reduced typing
* Statically typed
* Contains my own compiler written in C++
* Makes use of LLVM for IR to source code translation
### Data Types
| Data  Type        | Description                                                         |
| :---------------- | :-----------------------------------------------------------------: |
| String            |  |
| int               |  |
| bool              |  |
| float             |  |
| double            |  |
| char              |  |
### Syntax
* out() - displays text to the screen
* f - function declaration
* while
* if
* elif
* else
```
f int fizzbuzz(int n) {
  int i = 1;
  while i <= n {
    if i % 15 == 0 {
      out("fizzbuzz");
    } elif i % 3 == 0 {
      out("fizz");
    } elif i % 5 == 0 {
      out("buzz");
    } else {
      out(i);
    }
    i = i + 1;
  }

  return 90
}

fizzbuzz(15);
```
