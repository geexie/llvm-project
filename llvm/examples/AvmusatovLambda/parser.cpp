#include "ast.hpp"
#include "lexer.hpp"
#include "parser.hpp"

#include <cctype>
#include <cstdlib>

Expr* Parser::parseExpr() {
    std::string token = lexer->getToken();

    if (token == "") {
        return NULL;
    }

    if (std::isdigit(token[0])) {
        return new NumExpr(atoi(token.c_str()));
    }

    if (token[0] == '+') {
        Expr* op1 = parseExpr();
        Expr* op2 = parseExpr();
        return new AddExpr(op1, op2);
    }

    if (token[0] == '*') {
        Expr* op1 = parseExpr();
        Expr* op2 = parseExpr();
        return new MulExpr(op1, op2);
    }

    if (token[0] == '^') {
        Expr* op1 = parseExpr();
        Expr* op2 = parseExpr();
        return new PowExpr(op1, op2);
    }

    if (token[0] == 'x') {
        return new VarExpr();
    }

    return NULL;
}