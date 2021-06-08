#include "lexer.hpp"

#include <cctype>

std::string Lexer::getToken() {
  while (std::isspace(lastChar)) {
    lastChar = getchar();
  }

  if (std::isalpha(lastChar)) {
    std::string idStr;
    do {
      idStr += getNextChar();
    } while (std::isalnum(lastChar));
    return idStr;
  } else if (std::isdigit(lastChar)) {
    std::string numStr;
    do {
      numStr += getNextChar();
    } while (std::isdigit(lastChar));
    return numStr;
  } else if (lastChar == EOF) {
    return "";
  } else {
    std::string operatorStr;
    operatorStr = getNextChar();
    return operatorStr;
  }
} 