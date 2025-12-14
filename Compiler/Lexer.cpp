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
    QUOTATION,

    STRING,BOOL,CHAR,INT,
    FLOAT,ARRAY,DOUBLE,CONSTANT,

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

struct scanFlags
{
    bool justResolved;
    bool inString;
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

void addIdentifier(string unfinished) {

    // checking for longer reserved keywords such as int,bool etc

    if (unfinished == "out") {addToken(OUT,unfinished);}
    else if (unfinished == "int") {addToken(INT,unfinished);}
    else if (unfinished == "String") {addToken(STRING,unfinished);}
    else if (unfinished == "bool") {addToken(BOOL,unfinished);}
    else if (unfinished == "Array") {addToken(ARRAY,unfinished);}
    else if (unfinished == "float") {addToken(FLOAT,unfinished);}
    else if (unfinished == "double") {addToken(DOUBLE,unfinished);}
    else if (unfinished == "char") {addToken(CHAR,unfinished);}
    else if (unfinished == "return") {addToken(OUT,unfinished);}
    else if (unfinished == "const") {addToken(CONSTANT,unfinished);}
    else if (unfinished != ""){
        // this must be some kind of identifier such as x or y or a function name etc
        addToken(IDENTIFIER,unfinished);    
    }
}

scanFlags scanToken(string unfinished,char current,bool inString)
{
    
    // unfinished -> holds the current string that isnt currently related to any token (multi character tokens)
    // current -> current character the lexer is scanning through, this will always be 1 char ahead of unfinished
 
    bool foundTerminator = false;

    if (current == '"') {

        inString = !inString;

        if (inString) {
            addToken(QUOTATION, "QUOTATION");
        } else {
            addIdentifier(unfinished);
            addToken(QUOTATION,"QUOTATION");
        }

        foundTerminator = true;
    }

    if (!inString && !foundTerminator) {

         // looking for symbols that will terminate the longer keywords and identifiers

        if (isspace(current)) {
            addIdentifier(unfinished); 
            foundTerminator = true;
        }

        switch (current) {
            case '(': addIdentifier(unfinished); addToken(LEFT_PAREN,"("); foundTerminator = true; break;
            case ')': addIdentifier(unfinished); addToken(RIGHT_PAREN,")"); foundTerminator = true; break;
            case '{': addIdentifier(unfinished); addToken(LEFT_BRACE,"{"); foundTerminator = true; break;
            case '}': addIdentifier(unfinished); addToken(RIGHT_BRACE,"}"); foundTerminator = true; break;
            case ',': addIdentifier(unfinished); addToken(COMMA,","); foundTerminator = true; break;
            case '.': addIdentifier(unfinished); addToken(DOT,"."); foundTerminator = true; break;
            case ';': addIdentifier(unfinished); addToken(SEMICOLON,";"); foundTerminator = true; break;
            case '*': addIdentifier(unfinished); addToken(STAR,"*"); foundTerminator = true; break;
            case '-': addIdentifier(unfinished); addToken(MINUS,"-"); foundTerminator = true; break;
            case '+': addIdentifier(unfinished); addToken(PLUS,"+"); foundTerminator = true; break;
            case '&': addIdentifier(unfinished); addToken(ADDRESS,"&"); foundTerminator = true; break;
            case '=': addIdentifier(unfinished); addToken(EQUAL,"="); foundTerminator = true; break;
        }
    }

    return {foundTerminator,inString};
}

void scanSourceCode(string chosenFile) 
{

    string unfinishedToken; // holds a currently non-tokenable string as the loop may not have scanned full length of file yet ie 'ou' instead of keyword 'out'  
    scanFlags flags;
    bool inString = false;
    char currentChar; 

    // Reads 'SourceCode' file character by character 

    ifstream SourceCode(chosenFile);

    if (SourceCode.fail()) {
        cout << "ERROR LOADING FILE";
    } else {
        while (SourceCode.get(currentChar))
        {
            
            flags = scanToken(unfinishedToken,currentChar,inString);
            inString = flags.inString;

            if (flags.justResolved) { 
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
