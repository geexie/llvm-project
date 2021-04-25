#ifndef LEXER_HPP
#define LEXER_HPP

#include <string>
#include <cctype>

//to process a text file and recognize what it says

class Lexer{
public:
  Lexer() : lastChar(' ') {}
    //a “lexer” is used to break the input up into tokens
    //oken returned by the lexer includes a token code
  
  std::string getToken();

private:
  inline char getNextChar()
  {
    char c = lastChar;
    lastChar = getchar();
    return c;
  }

  char lastChar;
};
#endif