#include "VokhmyaninaAst.hpp"
#include "VokhmyaninaLexer.hpp"
#include "VokhmyaninaParser.hpp"

#include <cctype>
#include <cstdlib>

Expr* Parser::parseExpr() {
  std::string tk = lexer->getToken();

  if (tk == "") {
    return NULL;
  } 
  else if (std::isdigit(tk[0])) {
    return new NumExpr(atoi(tk.c_str()));
  }
  else if (tk[0] == 'x') {
    return new VarExpr();
  } 
  else if (tk[0] == '+') {
    Expr *op1 = parseExpr();
    Expr *op2 = parseExpr();
    return new AddExpr(op1, op2);
  } 
  else if (tk[0] == '*') {
    Expr *op1 = parseExpr();
    Expr *op2 = parseExpr();
    return new MulExpr(op1, op2);
  } 
  else if (tk[0] == '^') {
    Expr *op1 = parseExpr();
    Expr *op2 = parseExpr();
    return new PowExpr(op1, op2);
  } 
  else {
    return NULL;
  }
}
