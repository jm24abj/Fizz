#include <string>
#include "TokenTypes.h"

using namespace std;

class Token {

    public:
        TokenType type;
        string lexeme;
        int line;

        Token() {
            
        }

        Token(TokenType token_type, string lex, int token_line) {
            type = token_type;
            lexeme = lex;
            line = token_line;
        }

        string str() {
            return lexeme + "| line num " + to_string(line);
        }
};
