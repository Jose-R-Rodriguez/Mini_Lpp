%include{
	#include <cassert> 
	#include <iostream>
	#include "ast.hpp"
}
%token_type{const char* }
%type ids {Node*}
%type id_list {Node*}
%type primitive {Node*}
%type num_list {Node*}
%type nums {Node*}
%type global_decls {Node*}
%type fp_decls {Node*}
%type block {Node*}
%type opt_arg_list {Node*}
%type arg_list {Node*}
%type args {Node*}
%type variable_decls {Node*}
%type statement_list {Node*}
%type opt_params {Node*}
%type if_statement {Node*}
%type else_statement {Node*}
%type expr {Node*}
%type statement {Node*}
%type for_statement {Node*}
%type function_call {Node*}
%type assignment {Node*}
%type return_statement {Node*}

%syntax_error {
	extern unsigned int currentLine;
	extern unsigned int currentRow;
	std::cout<<"SYNTAX ERROR Column@:"<<currentLine<<" Row@:"<<currentRow<<std::endl;
	exit(1);
}

start ::= global_decls(A) fp_decls(B) block(C).				
								{std::cout<<A->toString()<<B->toString()<<C->toString()<<std::endl;}
global_decls(A) ::= global_decls(B) primitive(C) id_list(D) eol.									
								{A= new VariableDeclListNode(B, C, D);}
global_decls ::= global_decls primitive TK_OPEN_BRACK TK_NUM TK_CLOSE_BRACK id_list eol. 			
								{}
global_decls ::= global_decls typedef eol.					
								{}
global_decls ::= .											
								{}
eol ::= TK_NEW_LINE.										
								{}
eol ::= TK_EOF.												
								{}
id_list(A) ::= TK_ID(B) ids(C).								
								{A= new IdListNode(new IdNode(B), C);}
ids(A) ::= ids(B) TK_COMMA TK_ID(C).						
								{A= new IdListNode(new IdNode(C), B);}
ids(A) ::= .												
								{A= nullptr;}
primitive(A) ::= KW_ENTERO.									
								{A= new IntDeclNode();}
primitive(A) ::= KW_BOOLEANO.								
								{A= new BooleanDeclNode();}
primitive(A) ::= KW_CARACTER.								
								{A= new CharDeclNode();}
typedef ::= KW_TIPO TK_ID KW_ES primitive.					
								{}
typedef ::= KW_TIPO TK_ID KW_ES KW_ARREGLO TK_OPEN_BRACK num_list TK_CLOSE_BRACK KW_DE primitive. 	
								{}
num_list(A) ::= TK_NUM(B) nums(C).							
								{A= new NumListNode(C, new NumberNode(std::stoi(B)));}
nums(A) ::= nums(B) TK_COMMA TK_NUM(C).						
								{A=new NumListNode(B, new NumberNode(std::stoi(C)));}
nums(A) ::= .												
								{A=nullptr;}
fp_decls(A) ::= fp_decls(B) KW_PROC TK_ID(C) opt_arg_list(D) eol variable_decls(G) block(E).
								{A= new FuncsListNode(B, new ProcedureNode(new IdNode(C), D, E, G ));}
fp_decls(A) ::= fp_decls(B) KW_FUNC TK_ID(C) opt_arg_list(D) TK_COLON primitive(E)  TK_NEW_LINE opt_eol variable_decls(G) block(F).	
								{A= new FuncsListNode(B, new FunctionNode(new IdNode(C), D, E, F, G ));}
fp_decls(A) ::= .												
								{A= nullptr;}
opt_arg_list(A) ::= TK_OPEN_PAR arg_list(B) TK_CLOSE_PAR.
								{A= B;}
opt_arg_list(A) ::= .
								{A= nullptr;}
arg_list(A) ::= primitive(B) TK_ID(C) args(D).	
								{A= new ArgListNode(D, B, new IdNode(C));}
args(A) ::= args(B) TK_COMMA primitive(C) TK_ID(D).
								{A= new ArgListNode(B, C, new IdNode(D));}
args(A) ::= .							
								{A= nullptr;}
block(A) ::=  KW_INICIO opt_eol  statement_list(C) KW_FIN eol.
								{A= new BlockNode(C);}
opt_eol ::= opt_eol TK_NEW_LINE.
								{}
opt_eol ::= .
								{}
variable_decls(A) ::= variable_decls(B) primitive(C) id_list(D) eol.
								{A= new VariableDeclListNode(B, C, D);}
variable_decls(A) ::= variable_decls primitive(B) TK_OPEN_BRACK TK_NUM(C) TK_CLOSE_BRACK id_list(D) eol.	
								{A= new VariableDeclListNode(B, new NumberNode(std::stoi(C)), D );}
variable_decls(A) ::= .
								{A= nullptr;}
statement_list(A) ::= statement_list(B) statement(C) TK_NEW_LINE opt_eol.
								{A= new StatementListNode(B, C);}
statement_list(A) ::= .
								{A= nullptr;}
statement(A) ::= if_statement(B).
								{A= B;}
statement(A) ::= for_statement(B).
								{A= B;}
statement(A) ::= function_call(B).
								{A= B;}

statement(A) ::= assignment(B).
								{A= B;}
statement(A) ::= return_statement(B).
								{A= B;}
if_statement(A) ::= KW_SI expr(B) KW_ENTONCES statement_list(C) else_statement(D) KW_FIN KW_SI.
								{A= new IfStatementNode(A, B, C, D);}
else_statement(A) ::= KW_SINO statement_list(B).
								{A= new ElseStatementNode(B);}
else_statement(A) ::= .									
								{A= nullptr;}
for_statement(A) ::= KW_PARA assignment(B) KW_HASTA expr(C) KW_HAGA.	
								{A= new ForStatementNode(B, C);}
function_call(A) ::= KW_LLAMAR TK_ID(B) TK_OPEN_PAR opt_params(C) TK_CLOSE_PAR.
								{A= new FuncCallNode(new IdNode(B), C);}
opt_params(A) ::= expr(B) params(C).
								{A= new ParamListNode(C, B);}
opt_params(A) ::= .
								{A= nullptr;}
params(A) ::= params(B) TK_COMMA expr(C).
								{A= new ParamListNode(B, C);}
params ::= .
								{A= nullptr;}
left_val(A) ::= TK_ID(B).
								{A= new IdNode(B);}
left_val(A) ::= TK_ID(B) TK_OPEN_BRACK expr(C) TK_CLOSE_BRACK.
								{A= new ArrayAccessNode(B, C);}
function_use(A) ::= TK_ID(B) TK_OPEN_PAR opt_params(C) TK_CLOSE_PAR.
								{A= new FunctionUseNode(new IdNode(B), C);}
constant(A) ::= bool_const(B).
								{A= B;}
constant(A) ::= TK_NUM(B).
								{A= new NumberNode(std::stoi(B));}
constant(A) ::= TK_CHAR(B).
								{A= new CharNode(*B);}
bool_const(A) ::= KW_VERD(B).
								{A= new BooleanNode(strncmp(B,"verdadero",9) == 0)}
bool_const(A) ::= KW_FALSO(B).
								{A= new BooleanNode(strncmp(B,"falso",5) != 0)}
assignment ::= left_val TK_ARROW expr.
								{}
return_statement ::= KW_RETORNE expr.
								{}
expr ::= expr TK_MENOR_Q term0.
								{}
expr ::= expr TK_MAYOR_Q term0.
								{}
expr ::= expr TK_MAYOR_Q_IG term0.
								{}
expr ::= expr TK_MENOR_Q_IG term0.
								{}
expr ::= expr TK_IGUAL_Q term0.
								{}
expr ::= term0.				
								{}
term0 ::= term0 TK_SUMA term1.
								{}
term0 ::= term0 TK_RESTA term1.	
								{}
term0 ::= term0 TK_O term1.	
								{}
term0 ::= term1.		
								{}
term1 ::= term1 TK_MULT final.
								{}
term1 ::= term1 TK_DIV final.
								{}
term1 ::= term1 TK_PODER final.
								{}
term1 ::= term1 TK_Y final.	
								{}
term1 ::= term1 TK_MOD final.
								{}
term1 ::= final.
								{}
final ::= left_val.	
								{}
final ::= function_use.	
								{}
final ::= constant.		
								{}
final ::= TK_OPEN_PAR expr TK_CLOSE_PAR.
								{}