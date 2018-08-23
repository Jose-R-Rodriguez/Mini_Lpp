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
%x LINE_COMMENT
%x BLOCK_COMMENT
%x STR_LIT

%%
{id}				{ setLexeme(std::string(yytext)); return (Keywords.find(yytext) == Keywords.end()) ? TK_ID : Keywords[yytext]; }
{dec_num}			{ setLexeme(std::string(yytext)); return TK_NUM; }
\n					{ return TK_NEW_LINE; }
","					{ return TK_COMMA; }
"["					{ return TK_OPEN_BRACK; }
"]"					{ return TK_CLOSE_BRACK; }
"("					{ return TK_OPEN_PAR; }
")"					{ return TK_CLOSE_PAR; }
"+"					{ return TK_SUMA; }
"^"					{ return TK_PODER; }
"-"					{ return TK_RESTA; }
"<-"				{ return TK_ARROW; }
"<="				{ return TK_MENOR_Q_IG; }
"="					{ return TK_IGUAL_Q; }
">="				{ return TK_MAYOR_Q_IG; }
"<"					{ return TK_MENOR_Q; }
">"					{ return TK_MAYOR_Q; }
"*"					{ return TK_MULT;  }
"/"					{ return TK_DIV; }
"%"					{ return TK_MOD; }
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
