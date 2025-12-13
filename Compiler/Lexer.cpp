#include <iostream>
#include <string>
#include <fstream>

using namespace std;

enum TokenType {
    IDENTIFIER,
    
    LEFT_PAREN,RIGHT_PAREN,
    LEFT_BRACE,RIGHT_BRACE,
    COMMA,DOT,MINUS,PLUS,
    SEMICOLON,SLASH,STAR,ADDRESS,

    STRING,INT,FLOAT,
    CONST,BOOL,
    CHAR,POINTER,

    NOT,EQUAL,
    GREATER,LESS,

    AND,CLASS,ELSE,
    FALSE,FUNCTION,FOR,
    IF,NULL_EMPTY,OR,
    OUT,RETURN,THIS,WHILE
};

class Token {

    public:
        TokenType type;
        string lexeme;
        int line;

        Token(TokenType token_type, string lex, int token_line) {
            type = token_type;
            lexeme = lex;
            line = token_line;
        }

        string to_string() {
            return type + " : " + lexeme;
        }
};

void addToken(TokenType token,string lex)
{
    cout << lex;
    cout << "\n";
}

bool isNumeric(char character)
{
    return (character >= '0' && character <= '9');
}

bool isChar(char character)
{
    return (character >= 'a' && character <= 'z') || (character >= 'A' && character <= 'Z') || (character == '_');
}

bool isAlphaNumeric(char character) {
    return (isChar(character) || isNumeric(character));
}

bool scanToken(string unfinished,char current)
{
    
    // unfinished -> holds the current string that isnt currently related to any token (multi character tokens)
    // current -> current character the lexer is scanning through, this will always be 1 char ahead of unfinished
 
    bool foundTerminator = false;

    // looking for symbols that will terminate the longer keywords and identifiers

    if (isspace(current)) {
        foundTerminator = true;
    }

    switch (current) {
        case '"': break;
        case '(': addToken(LEFT_PAREN,"("); foundTerminator = true; break;
        case ')': addToken(RIGHT_PAREN,")"); foundTerminator = true; break;
        case '{': addToken(LEFT_BRACE,"{"); foundTerminator = true; break;
        case '}': addToken(RIGHT_BRACE,"}"); foundTerminator = true; break;
        case ',': addToken(COMMA,","); foundTerminator = true; break;
        case '.': addToken(DOT,"."); foundTerminator = true; break;
        case ';': addToken(SEMICOLON,";"); foundTerminator = true; break;
        case '*': addToken(STAR,"*"); foundTerminator = true; break;
        case '-': addToken(MINUS,"-"); foundTerminator = true; break;
        case '+': addToken(PLUS,"+"); foundTerminator = true; break;
        case '&': addToken(ADDRESS,"&"); foundTerminator = true; break;
        case '=': addToken(EQUAL,"="); foundTerminator = true; break;
    }

    // checking for longer reserved keywords such as int,bool etc

    if (foundTerminator) {
        if (unfinished == "out") {addToken(OUT,unfinished);}
        else if (unfinished == "int") {addToken(INT,unfinished);}
        else if (unfinished == "return") {addToken(OUT,unfinished);}
        else {
            // this must be some kind of identifier such as x or y or a function name etc
            cout << "new identifier: " + unfinished;
            cout << "\n";
        }
    }

    return foundTerminator;
}

void scanSourceCode(string chosenFile) 
{

    string unfinishedToken; // holds a currently non-tokenable string as the loop may not have scanned full length of file yet ie 'ou' instead of keyword 'out'  
    char currentChar; 

    // Reads 'SourceCode' file character by character 

    ifstream SourceCode(chosenFile);

    if (SourceCode.fail()) {
        cout << "ERROR LOADING FILE";
    } else {
        while (SourceCode.get(currentChar))
        {
            if (scanToken(unfinishedToken,currentChar)) { 
                // has found and resolved new token and can reset
                unfinishedToken = "";
            } else {
                unfinishedToken = unfinishedToken + currentChar;
            }
        }
    }

    SourceCode.close();
}

int main(int argc, char const *argv[])
{
    scanSourceCode("ExampleSourceCode/program2.txt");
    return 0;
}
