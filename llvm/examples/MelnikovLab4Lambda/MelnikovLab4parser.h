#ifndef MELNIKOVLAB4PARSER_H
#define MELNIKOVLAB4PARSER_H

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


#endif // MELNIKOVLAB4PARSER_H