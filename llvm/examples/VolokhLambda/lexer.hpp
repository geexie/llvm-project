#pragma once

#include <string>

class Lexer {
    public:
        Lexer() : lastChar(' ') {}

        // Token is a terminal sumbol for the grammar, a part of alphabet of lambda language
        // x, +, *, constant
        // TODO: implement as a finite automata
        std::string getToken();

    private:
        inline char getNextChar() {
            char c = lastChar;
            lastChar = getchar();
            return c;
        }

        char lastChar;
};