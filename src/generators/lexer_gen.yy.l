%option noyywrap
%option reentrant
%{
#include <istream>
#include "lexer.hpp"

#define YY_EXTRA_TYPE std::istream*
#define YY_INPUT(buf, result, max_size)\
	std::istream* input= yyget_extra(yyscanner);\
	input->read(buf, max_size);\
	result= input->gcount();
#define YY_DECL int Lexer::_ResolveToken (void* yyscanner)

%}

id			[a-zA-Z_][a-zA-Z0-9_]*
dec_num		[1-9][0-9]*
hex_num		"0"[xX][0-9]+
oct_num		"0"[0-8]+
binary_num	"0"[bB][01]+

%%
"Inicio"			{}
id					{}
%%

Lexer::Lexer(std::istream &input) : input(input){
	yylex_init_extra(&input, &myscanner);
}

Lexer::~Lexer(){
	yylex_destroy(myscanner);
}