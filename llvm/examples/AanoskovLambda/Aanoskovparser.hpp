#ifndef AANOSKOVPARSER_HPP
#define AANOSKOVPARSER_HPP

#include <string>

class aanoskovLexer;
class aanoskovExpr;

class aanoskovParser {
public:
  aanoskovParser(aanoskovLexer* argLexer) : lexer(argLexer) {}
  aanoskovExpr* parseExpr();
private:
  aanoskovLexer* lexer;
};

#endif // PARSER_HPP    
