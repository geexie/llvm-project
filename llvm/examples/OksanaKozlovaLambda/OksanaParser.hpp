#ifndef OKSANAPARSER_HPP
#define OKSANAPARSER_HPP

#include <string>

class OksanaLexer;
class OksanaExpr;

class OksanaParser {
public:
    OksanaParser(OksanaLexer* argLexer) : lexer(argLexer) {}
    OksanaExpr* parseExpr();
private:
    OksanaLexer* lexer;
};

#endif // OKSANAPARSER_HPP