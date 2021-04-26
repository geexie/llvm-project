#include "OksanaAST.hpp"
#include "OksanaLexer.hpp"
#include "OksanaParser.hpp"

#include <cctype>
#include <cstdlib>

OksanaExpr* OksanaParser::parseExpr() {
    std::string tk = lexer->getToken();

    if (tk == "") {
        return NULL;
    } else if (std::isdigit(tk[0])) {
        return new NumExpr(atoi(tk.c_str()));
    } else if (tk[0] == 'x') {
        return new VarExpr();
    } else if (tk[0] == '+') {
        OksanaExpr *op1 = parseExpr();
        OksanaExpr *op2 = parseExpr();
        return new AddExpr(op1, op2);
    } else if (tk[0] == '*') {
        OksanaExpr *op1 = parseExpr();
        OksanaExpr *op2 = parseExpr();
        return new MulExpr(op1, op2);
    } else if (tk[0] == '^') {
        OksanaExpr *op1 = parseExpr();
        OksanaExpr *op2 = parseExpr();
        return new PowExpr(op1, op2);
    } else {
        return NULL;
    }
} 