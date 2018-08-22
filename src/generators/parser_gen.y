%{
	#include "common.hpp"
	extern int yylex();
	void yyerror (char const *s) {
		std::cout<<s<<std::endl;
	}
%}

%defines "../src/hdrs/parser.hpp"


%token TK_STR_LIT
%token TK_ID
%token TK_NEW_LINE
%token TK_ADD
%token TK_EQUALS
%token TK_EQUALS_TO
%token TK_SUB
%token TK_DIV
%token TK_MULT
%token KW_START
%token KW_END
%token KW_INT
%token KW_BOOL
%token KW_CHAR
%token TK_NUM
%token KW_TYPEDEF
%token KW_IS
%token KW_ARRAY
%token KW_OF
%token TK_EOF 0
%token KW_PROC
%token KW_FUNC

%%
Start: Global_decls FP_decls Block													{}
;
Global_decls: Global_decls Primitive Id_list EOL 							{}
			| Global_decls Primitive "[" TK_NUM "]" Id_list EOL				{}
			| Global_decls Typedef TK_NEW_LINE 								{}
			|
;
EOL: TK_NEW_LINE
	|TK_EOF
;
Primitive: KW_BOOL															{}
			|KW_INT															{}
			|KW_CHAR														{}
;
Id_list: TK_ID	Ids															{}
;
Ids:Ids "," TK_ID															{}
	|
;
Typedef: KW_TYPEDEF TK_ID KW_IS Primitive									{}
		| KW_TYPEDEF TK_ID KW_IS KW_ARRAY "[" Num_list "]" KW_OF Primitive	{}
;
Num_list: TK_NUM Nums														{}
;
Nums: Nums "," TK_NUM														{}
	|
;
FP_decls: KW_PROC TK_ID Opt_Arg_list TK_NEW_LINE Block						{}
		| KW_FUNC TK_ID Opt_Arg_list ":" Primitive TK_NEW_LINE Block		{}
		|
;
Opt_Arg_list: "(" Arg_list ")"
			|
;
Arg_list: Primitive TK_ID Args
;
Args: Args "," Primitive TK_ID
;
Block:
;
%%