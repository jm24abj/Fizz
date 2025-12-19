#include "Lexer.h"
using namespace std;

// Recursive descent parser implementation

Token ahead_token;
int TokenPlace = 0;

void next() {
    if (TokenPlace < tokenStream.size()) {
        ahead_token = tokenStream.at(TokenPlace);
        TokenPlace = TokenPlace + 1;
        //cout << "Next token: " + ahead_token.str() + "\n";
    } else { 
        cout << "No more tokens to read.\n";
    }
    return; 
}

TokenType peekNext() {
    if (TokenPlace + 1 < tokenStream.size()) {
        return tokenStream.at(TokenPlace).type;
    }
    return NULL_EMPTY;
}

void showError(string contextText) {
    cout << "\n====================ERROR====================";
    cout << "\n" + contextText;
    cout << "\n";
    if (ahead_token.line == 1) {
        cout << "\nError on line " + to_string(ahead_token.line) + ".";
    } else {
        cout << "\nError on line " + to_string(ahead_token.line-1) + ".";
    }
    cout << "\n=============================================\n";
}

void showError(string contextText, int startingLine) {
    cout << "\n====================ERROR====================";
    cout << "\n" + contextText;
    cout << "\n";
    if (ahead_token.line == 1) {
        cout << "\nError on line " + to_string(ahead_token.line) + ".";
    } else {
        cout << "\nError on line " + to_string(ahead_token.line-1) + ".";
    }
    cout << " Starting on line " + to_string(startingLine) + ".";
    cout << "\n=============================================\n";
}

void function() {
    next();
    switch (ahead_token.type){
        case 0: break;
    }
}

bool stringContents(int startingLine) {
    next();
    switch (ahead_token.type) {
        case IDENTIFIER: 
            if (peekNext() != QUOTATION) {
                showError("String not terminated", startingLine);
                return false;
            } else {
                next(); // consumes ending quotation
                return true;
            }
            break;
        default:
            showError("invalid string contents");
    }
    return false;
}

bool operatorOrTerminator() {
    next();
    switch (ahead_token.type) {
        case PLUS: return true; break;
        case MINUS: return true; break;
        case STAR: return true; break;
        case SLASH: return true; break;
        case MOD: return true; break;
        case SEMICOLON: return false; break;
        default:
            showError("Assignment must be followed by operator or statement terminator");
    }

    return false;
}

void continuedAssignment() {
    while (operatorOrTerminator()) {
        next();
        switch (ahead_token.type) {
            case QUOTATION: stringContents(ahead_token.line); break;
            case TRUE: break;
            case FALSE: break;
            case IDENTIFIER: break;
            default:
                showError("invalid continued assignment");
        }
    }

    if (ahead_token.type != SEMICOLON) {
        showError("Statement must end with a semicolon");
    }
}

void assigment() {
    next();
    switch (ahead_token.type) {
        case QUOTATION: 
            if (stringContents(ahead_token.line)) { 
                continuedAssignment(); 
            }
            break;
        case TRUE: continuedAssignment(); break;
        case FALSE: continuedAssignment(); break;
        case IDENTIFIER: continuedAssignment(); break;
        default:
            showError("invalid assignment");
    }
}

void identifier() {
    next();
    switch (ahead_token.type) {
        case EQUAL: assigment(); break;
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
    int max = tokenStream.size();

    while ((ahead_token.type == SEMICOLON || TokenPlace == 0) && TokenPlace + 1 < max) {
        statement();
    }

    // checking for successful parsing
    
    next();
    if (ahead_token.type == ParsingSuccess) {
        cout << "\n\n\nSuccess!\n\n\n";
    }
}