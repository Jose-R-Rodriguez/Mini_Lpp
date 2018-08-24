#include <iostream>
#include <fstream>
#include "lexer.hpp"
#include "parser_lemon.hpp"
#include "parser.hpp"

int main(int argc, char const *argv[]){
	if (argc < 2) {
		std::cerr<<"Error no file inputted"<<std::endl;
		exit(1);
	}
	std::ifstream file(argv[1]);
	Lexer mylexer(file);
	void* pParser = ParseAlloc(malloc);

	int currentToken= mylexer.lex();
	while (currentToken != TK_EOF){
		std::cout<<currentToken<<"   "<<mylexer.getLexeme()<<std::endl;
		Parse(pParser, currentToken, mylexer.getLexeme().c_str());
		currentToken= mylexer.lex();
	}
	std::cout<<"Syntaxis good fam"<<std::endl;
	return 0;
}
