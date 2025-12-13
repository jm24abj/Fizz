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
    return (character >= 'a' && character <= 'z');
}

void scanToken()
{
    string text = next();

    if (text == " ") {}
    else if (text == "(") {addToken(LEFT_PAREN);}
    else if (text == ")") {addToken(RIGHT_PAREN);}
    else if (text == "{") {addToken(LEFT_BRACE);}
    else if (text == "}") {addToken(RIGHT_BRACE);}
    else if (text == ",") {addToken(COMMA);}
    else if (text == ".") {addToken(DOT);}
    else if (text == ";") {addToken(SEMICOLON);}
    else if (text == "*") {addToken(STAR);}
    else if (text == "-") {addToken(MINUS);}
    else if (text == "+") {addToken(PLUS);}
    else if (text == "&") {addToken(ADDRESS);}
    else if (isNumeric('a')) {

    } 
    else if (isChar('a')) {

    }
    else {
        
    }
}

void scanSourceCode() 
{
    /* code */

    // Create a text string, which is used to output the text file
    string currentLine;

    // Read from the text file
    ifstream MyReadFile("ExampleSourceCode/program2.txt");

    // Use a while loop together with the getline() function to read the file line by line
    while (getline(MyReadFile, currentLine)) {
        // Output the text from the file
        cout << currentLine + "\n";
    }

    // Close the file
    MyReadFile.close();
}

int main(int argc, char const *argv[])
{
    /* code */
    scanSourceCode();
    return 0;
}
