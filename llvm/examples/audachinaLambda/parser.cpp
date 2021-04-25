#include "ast.hpp"
#include "lexer.hpp"
#include "parser.hpp"

#include <cctype>
#include <cstdlib>
#include <iostream>

Expr* Parser::parseExpr() {
    std::string token = lexer->getToken();
    if (token==""){return NULL;}
    switch(token[0]){
        case 'x':
            return new VariableExpr();
            break;
        case '+':
            Expr* fOp = parseExpr();
            Expr* sOp = parseExpr();
            return new AddExpr(op1, op2);
            break;
        case '*':
            Expr* fOp = parseExpr();
            Expr* sOp = parseExpr();
            return new MultoplExpr(fOp, sOp);
            break;
        case '^':
            Expr* fOp = parseExpr();
            Expr* sOp = parseExpr();
            return new PowerExpr(fOp, sOp);
            break;
        default:
            return NULL;

  }
}