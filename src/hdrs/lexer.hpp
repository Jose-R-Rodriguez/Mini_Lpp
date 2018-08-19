#ifndef LEXER_HPP
#define LEXER_HPP
#include <istream>
#include "common.hpp"
#include "parser.hpp"

class Lexer{
public:
	Lexer (std::istream& input);
	int ResolveToken(){ return _ResolveToken(myscanner); }
private:
	int _ResolveToken(void*);
	std::istream& input;
	void* myscanner;
	~Lexer();
};
#endif