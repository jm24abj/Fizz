#include "Lexer.h"
using namespace std;

Token ahead_token;
int TokenPlace = 0;

void next() {
    ahead_token = tokenStream.at(TokenPlace);
    TokenPlace = TokenPlace + 1;
    //cout << ahead_token.lexeme;
    //cout << "\n";
    return; 
}

void showError(string contextText) {
    cout << "\n" + contextText;
    cout << "\n";
    cout << "\nError on line " + to_string(ahead_token.line-1) + ".";
}

void function() {
    next();
    switch (ahead_token.type){
        case 0: break;
    }
}

void statementTerminator() {
    next();
    switch (ahead_token.type) {
        case SEMICOLON: break;
        default:
            showError("No statement terminator");
    } 
}

void endString() {
    next();
    switch (ahead_token.type) {
        case QUOTATION: statementTerminator(); break;
        default:
            showError("didnt end string");
    }
}

void stringContents() {
    next();
    switch (ahead_token.type) {
        case IDENTIFIER: endString(); break;
        default:
            showError("invalid string contents");
    }
}

void equals() {
    next();
    switch (ahead_token.type) {
        case QUOTATION: stringContents(); break;
        case TRUE: statementTerminator(); break;
        case FALSE: statementTerminator(); break;
        case IDENTIFIER: statementTerminator(); break;
        default:
            showError("invalid assignment");
    }
}

void identifier() {
    next();
    switch (ahead_token.type) {
        case EQUAL: equals(); break;
        default:
            showError("invalid operator");
    }
}

void dataType() {
    next();
    switch (ahead_token.type) {
        case IDENTIFIER: identifier(); break;
        default:
            showError("invalid identifier name");
    }
}

void statement() {
    next();
    switch (ahead_token.type){
        case STRING: dataType(); break;
        case INT: dataType(); break;
        case BOOL: dataType(); break;
        case FLOAT: dataType(); break;
        case CHAR: dataType(); break;
        case DOUBLE: dataType(); break;

        case IDENTIFIER: identifier(); break;
        case FUNCTION: function(); break;
        default:
            showError("invalid statement...check if data type or function starter is correct");
    }
}

void testRecievedTokens() { // for debugging (prints out tokens one after the other)
    tokenStream.push_back(Token(ParsingSuccess,"",0));
    next();
    while (ahead_token.type != ParsingSuccess)
    {
        cout << ahead_token.lexeme;
        cout << "\n";
        next();
    }
} 

void beginParse() {
    cout << to_string(tokenStream.size()) + ":";
    tokenStream.push_back(Token(ParsingSuccess,"",0));
    cout << to_string(tokenStream.size()) + "\n";

    int max = tokenStream.size();

    while ((ahead_token.type == SEMICOLON || TokenPlace == 0) && TokenPlace + 1 < max) {
        statement();
    }

    // checking for successful parsing
    
    next();
    if (ahead_token.type == ParsingSuccess) {
        cout << "Success!";
    }
}