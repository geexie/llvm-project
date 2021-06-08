#ifndef OKSANALEXER_HPP
#define OKSANALEXER_HPP

#include <string>

class OksanaLexer {
public:
  OksanaLexer() : lastChar(' ') {}
  std::string getToken();

private:
  inline char getNextChar() {
    char c = lastChar;
    lastChar = getchar();
    return c;
  }

  char lastChar;
};

#endif // OKSANALEXER_HPP 