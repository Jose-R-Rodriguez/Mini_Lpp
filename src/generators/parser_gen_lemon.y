%include{ 
	#include <cassert> 
	#include <iostream>
}
%token_type{const char*}
%syntax_error {
	std::cout<<"SYNTAX ERROR"<<std::endl;
	exit(1);
}

start ::= global_decls. 									{ std::cout<<"Found Declaration"<<std::endl; }
global_decls ::= primitive id_list eol.						{}
eol ::= TK_NEW_LINE.										{}
eol ::= TK_EOF.												{}
id_list ::= TK_ID ids.										{}
ids ::= ids TK_COMMA TK_ID.									{}
ids ::= .													{}
primitive ::= KW_ENTERO.									{}