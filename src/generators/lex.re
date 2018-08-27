#include "lexer.hpp"

/*!max:re2c*/
/*!types:re2c*/


bool input_t::fill(size_t need){
	if (eof) {
		return false;
	}
	const size_t free = tok - buf;
	if (free < need) {
		return false;
	}
	memmove(buf, tok, lim - tok);
	lim -= free;
	cur -= free;
	tok -= free;
	mar -= free;
	in.read(lim, free);
	lim+= in.gcount();
	if (lim < buf + SIZE) {
		eof = true;
		memset(lim, 0, YYMAXFILL);
		lim += YYMAXFILL;
	}
	return true;
};

input_t::input_t (std::istream &in) : in(in){
	buf= new char[SIZE + YYMAXFILL];
	lim= buf+SIZE;
	cur= lim;
	tok= lim;
	mar= lim;
	eof= false;
}
unsigned int currentRow= 1;
unsigned int currentLine= 1;

int Lexer::lex() {
	while (1){
		in.tok = in.cur;
		int c = -1;
		/*!re2c
			re2c:define:YYCTYPE = char;
			re2c:define:YYCURSOR = in.cur;
			re2c:define:YYLIMIT = in.lim;
			re2c:define:YYFILL = "if (!in.fill(@@)) return false;";
			re2c:define:YYFILL:naked = 1;
			re2c:define:YYMARKER= in.mar;

			re2c:define:YYGETCONDITION = "c";
			re2c:define:YYGETCONDITION:naked = 1;
			re2c:define:YYSETCONDITION = "c = @@;";
			re2c:define:YYSETCONDITION:naked = 1;

			id=			[a-zA-Z_][a-zA-Z0-9_]*;
			dec_num=	[1-9][0-9]*;

			<!main>						{ int yylen= in.cur-in.tok; lexeme = std::string(in.tok, yylen); currentLine+= yylen;}
			<main>id      				{ return (Keywords.find(lexeme) == Keywords.end()) ? TK_ID : Keywords[lexeme]; }
			<main>dec_num				{ return TK_NUM; }
			<main>"+"					{ return TK_SUMA; }
			<main>"*"					{ return TK_MULT; }
			<main>"/"					{ return TK_DIV; }
			<main>"^"					{ return TK_PODER; }
			<main>"-"					{ return TK_RESTA; }
			<main>"<-"					{ return TK_ARROW; }
			<main>"<="					{ return TK_MENOR_Q_IG; }
			<main>"="					{ return TK_IGUAL_Q; }
			<main>">="					{ return TK_MAYOR_Q_IG; }
			<main>"<"					{ return TK_MENOR_Q; }
			<main>">"					{ return TK_MAYOR_Q; }
			<main>"%"					{ return TK_MOD; }
			<main>"\'"[0-255]"\'"		{ return TK_CHAR;}
			<main>"("					{ return TK_OPEN_PAR; }
			<main>")"					{ return TK_CLOSE_PAR; }
			<main>","					{ return TK_COMMA; }
			<main>"["					{ return TK_OPEN_BRACK; }
			<main>"]"					{ return TK_CLOSE_BRACK; }
			<main>":"					{ return TK_COLON; }
			<main>"\n"					{ ++currentRow; currentLine=1;return TK_NEW_LINE; }
			<main>" "					{ continue; }
			<main>*						{ 
					if (!in.eof){std::cout<<"UNKNOWN TOKEN"<<lexeme<<std::endl; 
					exit(1);} 
					else{return TK_EOF;} 
				}

			<main>"\""					{lexeme= ""; goto yyc_str_lit;}
			<main>"//"					{lexeme= ""; goto yyc_line_comment;}
			<line_comment>.				:=>line_comment
			<line_comment>"\n"			:=>main
			<str_lit>[^"]*				{lexeme+=*in.tok; goto yyc_str_lit;}
			<str_lit>"\""				{return TK_STR_LIT;}
		*/
	}
};