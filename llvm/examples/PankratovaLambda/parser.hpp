#ifndef PARSER_HPP
#define PARSER_HPP

#include <string>

class Lexer;
class Expr;

class Parser {
  public:
    Parser(Lexer* argLexer) : lexer(argLexer) {}
    Expr* parseExpr();
  private:
    Lexer* lexer;
};

#endif // PARSER_HPP
