%{
	#include "common.hpp"
	extern int yylex();
	void yyerror (char const *s) {
		std::cout<<s<<std::endl;
	}
%}

%defines "../src/hdrs/parser.hpp"

%token TK_ADD
%token TK_SUB
%%
	test: ;
%%