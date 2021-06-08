#ifndef MELNIKOVLAB4LEXER_H
#define MELNIKOVLAB4LEXER_H

#include <string>


class Lexer {
private:
    char lastChar;

    inline char getNextChar() {
        char c = lastChar;
        lastChar = getchar();
        return c;
    }


public:
    Lexer() : lastChar(' ') {}
    std::string getToken(); // next token

};



#endif // LEXER_H