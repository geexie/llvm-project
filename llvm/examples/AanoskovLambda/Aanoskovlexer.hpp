#ifndef AANOSKOVLEXER_HPP
#define AANOSKOVLEXER_HPP

#include <string>

class aanoskovLexer {
public:
  aanoskovLexer() : lastChar(' ') {}

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

#endif // LEXER_HPP