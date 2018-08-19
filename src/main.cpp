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
	int currToken= mylexer->ResolveToken();
	while (currToken != 0) {
		std::cout<<currToken<<std::endl;
		currToken= mylexer->ResolveToken();
	}
	return 0;
}
