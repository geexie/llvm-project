#include "ast.hpp"
#include "lexer.hpp"
#include "parser.hpp"
#include <cctype>
#include <cstdlib>

Expr* Parser::parseExpr() {
	std::string token = lexer->getToken();
	if (token == "") {
		return nullptr;
	}
	else if (std::isdigit(token[0])) {
		return new NumExpr(atoi(token.c_str()));
	}
	else if (token[0] == 'x') {
		return new VarExpr();
	}
	else if (token[0] == '+') {
		Expr* op1 = parseExpr();
		Expr* op2 = parseExpr();
		return new AddExpr(op1, op2);
	}
	else if (token[0] == '*') {
		Expr* op1 = parseExpr();
		Expr* op2 = parseExpr();
		return new MulExpr(op1, op2);
	}
	else if (token[0] == '^') {
		Expr* op1 = parseExpr();
		Expr* op2 = parseExpr();
		return new PowExpr(op1, op2);
	}
	else {
		return nullptr;
	}
}