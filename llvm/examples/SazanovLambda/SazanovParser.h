#ifndef SAZANOV_PARSER_H
#define SAZANOV_PARSER_H

#include <string>

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

#endif // SAZANOV_PARSER_H
