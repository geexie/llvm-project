#pragma once


#include <string>
#include <cctype>
#include <cstdlib>

class Lexer;
class Expr;

class Parser
{
public:
  Parser(Lexer* argLexer) : lexer(argLexer) {}
  Expr* parseExpr();
private:
  Lexer* lexer;
};