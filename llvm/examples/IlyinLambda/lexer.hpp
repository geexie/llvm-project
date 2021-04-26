#pragma once

#include <string>

class Lexer {
private:
	inline char getNextChar() {
		char c = lastChar;
		lastChar = getchar();
		return c;
	}
	char lastChar;

public:
	Lexer() : lastChar(' ') {}
	std::string getToken();
};
