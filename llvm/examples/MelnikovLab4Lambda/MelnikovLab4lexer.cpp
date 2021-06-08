#include "MelnikovLab4lexer.h"

#include <cctype>


std::string Lexer::getToken() {
    while (std::isspace(lastChar)) { // skip if space
        lastChar = getchar();
    }

    if (std::isalpha(lastChar)) { // a string of characters
        std::string idStr;
        do {
            idStr += getNextChar();
        } while (std::isalnum(lastChar));
        return idStr;   

    }
    else if (std::isdigit(lastChar)) { // a number
        std::string numStr;
        do {
            numStr += getNextChar();
        } while (std::isdigit(lastChar));
        return numStr;
    }
    else if (lastChar == EOF) {
        return "";
    }
    else { // if nothing of the above, then it's an operator
        std::string operatorStr;
        operatorStr = getNextChar();
        return operatorStr;
    }
}