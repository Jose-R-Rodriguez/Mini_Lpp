%include{
	#include <cassert> 
	#include <iostream>
}
%token_type{const char*}
%syntax_error {
	std::cout<<"SYNTAX ERROR"<<std::endl;
	exit(1);
}

start ::= global_decls fp_decls block.						{ std::cout<<"Found Declaration"<<std::endl; }
global_decls ::= global_decls primitive id_list eol.		{}
global_decls ::= global_decls primitive TK_OPEN_BRACK TK_NUM TK_CLOSE_BRACK id_list eol. 			{}
global_decls ::= global_decls typedef eol.					{}
global_decls ::= .											{}
eol ::= TK_NEW_LINE.										{}
eol ::= TK_EOF.												{}
id_list ::= TK_ID ids.										{}
ids ::= ids TK_COMMA TK_ID.									{}
ids ::= .													{}
primitive ::= KW_ENTERO.									{}
primitive ::= KW_BOOLEANO.									{}
primitive ::= KW_CARACTER.									{}
typedef ::= KW_TIPO TK_ID KW_ES primitive.					{}
typedef ::= KW_TIPO TK_ID KW_ES KW_ARREGLO TK_OPEN_BRACK num_list TK_CLOSE_BRACK KW_DE primitive. 	{}
num_list ::= TK_NUM nums.									{}
nums ::= nums TK_COMMA TK_NUM.								{}
nums ::= .													{}
fp_decls ::= KW_PROC TK_ID opt_arg_list eol block.			{}
fp_decls ::= KW_FUNC TK_ID opt_arg_list TK_COLON primitive eol block.								{}
fp_decls ::= .												{}
opt_arg_list ::= TK_OPEN_PAR arg_list TK_CLOSE_PAR.			{}
opt_arg_list ::= .											{}
arg_list ::= primitive TK_ID args.							{}
args ::= args TK_COMMA primitive TK_ID.						{}
args ::= .													{}
block ::= KW_INICIO variable_decls statement_list KW_FIN eol.	{}
variable_decls ::= primitive id_list eol.					{}
variable_decls ::= primitive TK_OPEN_BRACK TK_NUM TK_CLOSE_BRACK id_list eol.						{}
variable_decls ::= .										{}
statement_list ::= statement_list statement eol.			{}
statement_list ::= .										{}
statement ::= if_statement.									{}
statement ::= for_statement.								{}
statement ::= function_call.								{}

statement ::= assignment.									{}
statement ::= return_statement.								{}
if_statement ::= KW_SI expr KW_ENTONCES statement_list else_statement KW_FIN KW_SI.					{}
else_statement ::= KW_SINO statement_list.					{}
else_statement ::= .										{}
for_statement ::= KW_PARA assignment KW_HASTA expr KW_HAGA.	{}
function_call ::= KW_LLAMAR TK_ID TK_OPEN_PAR opt_params TK_CLOSE_PAR eol.							{}
opt_params ::= TK_NUM params.								{}
opt_params ::= TK_ID params.								{}
params ::= params TK_COMMA expr.							{}
params ::= .												{}
expr ::= left_val.											{}
expr ::= function_use.										{}
expr ::= constant.											{}
left_val ::= TK_ID.											{}
left_val ::= TK_ID TK_OPEN_BRACK expr TK_CLOSE_BRACK.		{}
function_use ::= TK_ID TK_OPEN_PAR opt_params TK_CLOSE_PAR eol.	{}
constant ::= bool_const.									{}
constant ::= TK_NUM.										{}
constant ::= TK_CHAR.										{}
bool_const ::= KW_VERD.										{}
bool_const ::= KW_FALSO.									{}
assignment ::= left_val TK_ARROW expr eol.					{}
return_statement ::= KW_RETORNE expr.						{}