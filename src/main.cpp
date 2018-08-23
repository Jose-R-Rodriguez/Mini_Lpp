#include <iostream>
#include <fstream>
#include "lexer.hpp"
#include "parser_lemon.hpp"
#include "parser.hpp"
Lexer* mylexer;
int main(int argc, char const *argv[]){
	if (argc < 2) {
		std::cerr<<"Error no file inputted"<<std::endl;
		exit(1);
	}
	std::ifstream file(argv[1]);
	mylexer= new Lexer(file);
	void* pParser = ParseAlloc(malloc);
	int currentToken=-1;
	while (currentToken != TK_EOF){
		std::cout<<"IN HERE: "<<currentToken<<std::endl;
		currentToken= mylexer->ResolveToken();
		Parse(pParser, currentToken, mylexer->getLexeme().c_str());
	}
	return 0;
}
