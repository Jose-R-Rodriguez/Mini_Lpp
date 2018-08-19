#include <iostream>
#include <fstream>
#include "lexer.hpp"
Lexer* mylexer;
int yylex(){ return mylexer->ResolveToken(); }

int main(int argc, char const *argv[]){
	if (argc < 2) {
		std::cerr<<"Error no file inputted"<<std::endl;
		exit(1);
	}
	std::ifstream file(argv[1]);
	mylexer= new Lexer(file);
	std::cout<<mylexer->ResolveToken()<<std::endl;
	return 0;
}
