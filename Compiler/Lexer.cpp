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

    AND,CLASS,ELSE,ELIF,
    FALSE,FUNCTION,FOR,
    IF,NULL_EMPTY,OR,
    OUT,RETURN,WHILE,VOID
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

        string str() {
            return lexeme + "| line num " + to_string(line);
        }
};

struct scanFlags
{
    bool justResolved;
    bool inString;
    bool commentFound;
};

void addToken(TokenType token,string lex,int lineNumber)
{
    Token newToken(token,lex,lineNumber);
    cout << newToken.str();
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

void addIdentifier(string unfinished,int lineNumber) {

    // checking for longer reserved keywords such as int,bool etc

    if (unfinished == "f") {addToken(FUNCTION,"function",lineNumber); return;}

    if (unfinished == "out") {addToken(OUT,unfinished,lineNumber); return;}

    else if (unfinished == "int") {addToken(INT,unfinished,lineNumber); return;}
    else if (unfinished == "String") {addToken(STRING,unfinished,lineNumber); return;}
    else if (unfinished == "bool") {addToken(BOOL,unfinished,lineNumber); return;}
    else if (unfinished == "Array") {addToken(ARRAY,unfinished,lineNumber); return;}
    else if (unfinished == "float") {addToken(FLOAT,unfinished,lineNumber); return;}
    else if (unfinished == "void") {addToken(VOID,unfinished,lineNumber); return;}
    else if (unfinished == "double") {addToken(DOUBLE,unfinished,lineNumber); return;}
    else if (unfinished == "char") {addToken(CHAR,unfinished,lineNumber); return;}
    else if (unfinished == "const") {addToken(CONSTANT,unfinished,lineNumber); return;}

    else if (unfinished == "if") {addToken(IF,unfinished,lineNumber); return;}
    else if (unfinished == "elif") {addToken(ELIF,unfinished,lineNumber); return;}
    else if (unfinished == "else") {addToken(ELSE,unfinished,lineNumber); return;}
    else if (unfinished == "while") {addToken(WHILE,unfinished,lineNumber); return;}
    else if (unfinished == "for") {addToken(FOR,unfinished,lineNumber); return;}

    else if (unfinished == "return") {addToken(OUT,unfinished,lineNumber); return;}

    else if (unfinished != ""){ // this must be some kind of identifier such as x or y or a function name etc
        addToken(IDENTIFIER,unfinished,lineNumber);    
        return; 
    }
}

scanFlags scanToken(string unfinished,char current,bool inString,int lineNumber)
{
    
    // unfinished -> holds the current string that isnt currently related to any token (multi character tokens)
    // current -> current character the lexer is scanning through, this will always be 1 char ahead of unfinished
 
    bool foundTerminator = false;

    if (current == '"') {

        inString = !inString;

        if (inString) {
            addToken(QUOTATION, "QUOTATION",lineNumber);
        } else {
            addIdentifier(unfinished,lineNumber);
            addToken(QUOTATION,"QUOTATION",lineNumber);
        }

        foundTerminator = true;
    }

    if (!inString && !foundTerminator) {

         // looking for symbols that will terminate the longer keywords and identifiers

        if (isspace(current)) {
            addIdentifier(unfinished,lineNumber); 
            foundTerminator = true;
        }

        switch (current) {
            case '#': foundTerminator = true; return {foundTerminator,inString,true}; // checks for single line comments
            case '(': addIdentifier(unfinished,lineNumber); addToken(LEFT_PAREN,"(",lineNumber); foundTerminator = true; break;
            case ')': addIdentifier(unfinished,lineNumber); addToken(RIGHT_PAREN,")",lineNumber); foundTerminator = true; break;
            case '{': addIdentifier(unfinished,lineNumber); addToken(LEFT_BRACE,"{",lineNumber); foundTerminator = true; break;
            case '}': addIdentifier(unfinished,lineNumber); addToken(RIGHT_BRACE,"}",lineNumber); foundTerminator = true; break;
            case ',': addIdentifier(unfinished,lineNumber); addToken(COMMA,",",lineNumber); foundTerminator = true; break;
            case '.': addIdentifier(unfinished,lineNumber); addToken(DOT,".",lineNumber); foundTerminator = true; break;
            case ';': addIdentifier(unfinished,lineNumber); addToken(SEMICOLON,";",lineNumber); foundTerminator = true; break;
            case '*': addIdentifier(unfinished,lineNumber); addToken(STAR,"*",lineNumber); foundTerminator = true; break;
            case '-': addIdentifier(unfinished,lineNumber); addToken(MINUS,"-",lineNumber); foundTerminator = true; break;
            case '+': addIdentifier(unfinished,lineNumber); addToken(PLUS,"+",lineNumber); foundTerminator = true; break;
            case '&': addIdentifier(unfinished,lineNumber); addToken(ADDRESS,"&",lineNumber); foundTerminator = true; break;
            case '=': addIdentifier(unfinished,lineNumber); addToken(EQUAL,"=",lineNumber); foundTerminator = true; break;
        }
    }

    return {foundTerminator,inString,false};
}

void scanSourceCode(string chosenFile) 
{

    string unfinishedToken; // holds a currently non-tokenable string as the loop may not have scanned full length of file yet ie 'ou' instead of keyword 'out'  
    unfinishedToken = "";

    scanFlags flags;

    flags.justResolved = false;
    flags.inString = false;
    flags.commentFound = false;

    string currentLine;
    char currentChar; 
    int lineNum = 1;

    // Reads 'SourceCode' file character by character 

    ifstream SourceCode(chosenFile);

    if (SourceCode.fail()) {
        cout << "ERROR LOADING FILE";
    } else {
        while (getline(SourceCode, currentLine)) { // determines line number
            for (int i = 0; i < currentLine.size(); i++) 
            {
                currentChar = currentLine[i];

                flags = scanToken(unfinishedToken,currentChar,flags.inString,lineNum);
                
                if (flags.commentFound) {
                    unfinishedToken = "";
                    break;
                } else {

                    if (flags.justResolved) { 
                        // has found and resolved new token and can reset
                        unfinishedToken = "";
                    } else {
                        unfinishedToken = unfinishedToken + currentChar;
                    }
                }

                //cout << "done " + unfinishedToken + "\n";
            }

            lineNum = lineNum + 1;
        }
    }

    SourceCode.close();
}

int main(int argc, char const *argv[])
{
    scanSourceCode("ExampleSourceCode/program5.txt");
    return 0;
}
