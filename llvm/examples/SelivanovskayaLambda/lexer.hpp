#pragma once

#include <string>
#include <cctype>

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