#ifndef PARSER_HPP
#define PARSER_HPP

#include <string>
#include <cctype>
#include <cstdlib>


class Expr; //expression nodes
class Lexer; //lexical analysis

//parser is for syntactic analysis
class Parser {
  public:
    Parser(Lexer* argLexer) : lexer(argLexer) {}
    Expr* parseExpr();
  private:
    Lexer* lexer;
};
#endif