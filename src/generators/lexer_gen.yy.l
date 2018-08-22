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

%option caseless
id			[a-zA-Z_][a-zA-Z0-9_]*
dec_num		[1-9][0-9]*
hex_num		"0x"[0-9]+
oct_num		"0"[0-8]+
binary_num	"0b"[01]+
%x LINE_COMMENT
%x BLOCK_COMMENT
%x STR_LIT

%%
{id}				{ setLexeme(std::string(yytext)); return (Keywords.find(yytext) == Keywords.end()) ? TK_ID : Keywords[yytext]; }
\n					{ return TK_NEW_LINE; }
"\""				{ BEGIN(STR_LIT); }
"//"				{ BEGIN(LINE_COMMENT); }
"/*"				{ BEGIN(BLOCK_COMMENT); }
.					{ ; }
<STR_LIT>[^"]*		{ ; }
<STR_LIT>\"			{BEGIN(INITIAL); return TK_STR_LIT; }
<LINE_COMMENT>.		{ ; }
<LINE_COMMENT>\n	{ BEGIN(INITIAL); }
<BLOCK_COMMENT>.|\n	{}
<BLOCK_COMMENT>"*/"	{ BEGIN(INITIAL); }
<<EOF>>				{ return TK_EOF; }
%%

Lexer::Lexer(std::istream &input) : input(input){
	yylex_init_extra(&input, &myscanner);
}

Lexer::~Lexer(){
	yylex_destroy(myscanner);
}