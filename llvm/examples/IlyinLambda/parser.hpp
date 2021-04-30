#pragma once

#include <string>

class Lexer;
class Expr;

class Parser {
private:
	Lexer* lexer;

public:
	Parser(Lexer* argLexer) : lexer(argLexer) {}
	Expr* parseExpr();
};
