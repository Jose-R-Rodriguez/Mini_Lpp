#include <iostream>
#include <fstream>
#include <stack>
#include <memory>
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


	
	using unique_str_ptr = std::unique_ptr<std::string>;
	using unique_ptr_pool = std::stack<unique_str_ptr>;
	unique_ptr_pool inputStrings;

	int currentToken= -1;
	while (currentToken != TK_EOF){
		currentToken= mylexer.lex();
		auto temp = std::make_unique<std::string>(mylexer.getLexeme());
		inputStrings.push(std::move(temp));
		Parse(pParser, currentToken, inputStrings.top().get()->c_str());
	}
	std::cout<<"Syntax good"<<std::endl;
	return 0;
}
