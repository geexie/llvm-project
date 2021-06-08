#include "Aanoskovast.hpp"
#include "Aanoskovlexer.hpp"
#include "Aanoskovparser.hpp"

#include <cctype>
#include <cstdlib>

aanoskovExpr* aanoskovParser::parseExpr() {
  std::string tk = lexer->getToken();

  if (tk == "") {
    return NULL;
  } else if (std::isdigit(tk[0])) {
    return new NumExpr(atoi(tk.c_str()));
  } else if (tk[0] == 'x') {
    return new VarExpr();
  } else if (tk[0] == '+') {
    aanoskovExpr *op1 = parseExpr();
    aanoskovExpr *op2 = parseExpr();
    return new AddExpr(op1, op2); 
  } else if (tk[0] == '*') {
    aanoskovExpr *op1 = parseExpr();
    aanoskovExpr *op2 = parseExpr();
    return new MulExpr(op1, op2);
  } else if (tk[0] == '^') {
      aanoskovExpr *op1 = parseExpr();
      aanoskovExpr *op2 = parseExpr();
      return new PowExpr(op1, op2);
  }
  else {
    return NULL;
  }
}