#pragma once

#include <string>

class Lexer {
public:
    Lexer() : lastChar(' ') {}
    std::string getToken();

private:
    inline char getNextChar() {
        char c = lastChar;
        lastChar = getchar();
        return c;
    }

    char lastChar;
};