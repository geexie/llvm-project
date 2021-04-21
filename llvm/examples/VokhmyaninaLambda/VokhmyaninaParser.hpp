#pragma once

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
