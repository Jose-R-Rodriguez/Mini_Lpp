%include{
	#include <cassert> 
	#include <iostream>
	#include "ast.hpp"
}
%token_type{const char* }
%type ids {AstNode*}
%type id_list {AstNode*}
%type primitive {AstNode*}
%type num_list {AstNode*}
%type nums {AstNode*}
%type global_decls {AstNode*}
%type fp_decls {AstNode*}
%type block {AstNode*}
%type opt_arg_list {AstNode*}
%type arg_list {AstNode*}
%type args {AstNode*}
%type variable_decls {AstNode*}
%type statement_list {AstNode*}
%type opt_params {AstNode*}
%type if_statement {AstNode*}
%type else_statement {AstNode*}
%type expr {AstNode*}
%type statement {AstNode*}
%type for_statement {AstNode*}
%type function_call {AstNode*}
%type assignment {AstNode*}
%type return_statement {AstNode*}
%type params {AstNode*}
%type constant {AstNode*}
%type bool_const {AstNode*}
%type left_val {AstNode*}
%type function_use {AstNode*}
%type term0 {AstNode*}
%type term1 {AstNode*}
%type final {AstNode*}
%type typedef {AstNode*}
%type expr_list{AstNode*}
%type exprs{AstNode*}




%syntax_error {
	extern unsigned int currentLine;
	extern unsigned int currentRow;
	std::cout<<"SYNTAX ERROR Column@:"<<currentLine<<" Row@:"<<currentRow<<std::endl;
	exit(1);
}

start ::= global_decls(A) fp_decls(B) block(C) TK_EOF.				
								{
									std::cout<<"Analyzing..."<<std::endl;
									AstNode* program = new ProgramNode(A,B,C);
									//std::cout<<program->toString();
									program->doSemantics();
								}
global_decls(A) ::= global_decls(B) primitive(C) id_list(D) one_more_eol.									
								{A= new VariableDeclListNode({B, C, D});}
global_decls(A) ::= global_decls(B) primitive(C) TK_OPEN_BRACK TK_NUM(D) TK_CLOSE_BRACK id_list(E) one_more_eol. 			
								{A= new VariableDeclListNode({B, C, new NumberNode(std::stoi(D)), E});}
global_decls(A) ::= global_decls(B) typedef(C) one_more_eol.					
								{A= new VariableDeclListNode({B, C});}
global_decls(A) ::= .
								{A= nullptr;}
one_more_eol ::= opt_eol TK_NEW_LINE.
								{}
id_list(A) ::= TK_ID(B) ids(C).
								{A= new IdListNode({new IdNode(B), C});}
ids(A) ::= ids(B) TK_COMMA TK_ID(C).						
								{A= new IdListNode({new IdNode(C), B});}
ids(A) ::= .												
								{A= nullptr;}
primitive(A) ::= KW_ENTERO.									
								{A= new IntDeclNode();}
primitive(A) ::= KW_BOOLEANO.								
								{A= new BooleanDeclNode();}
primitive(A) ::= KW_CARACTER.								
								{A= new CharDeclNode();}
typedef(A) ::= KW_TIPO TK_ID(B) KW_ES primitive(C).					
								{A= new TypedefNode(new IdNode(B), C);}
typedef(A) ::= KW_TIPO TK_ID(B) KW_ES KW_ARREGLO TK_OPEN_BRACK num_list(C) TK_CLOSE_BRACK KW_DE primitive(D). 	
								{A= new TypedefArrayNode(new IdNode(B), C, D);}
num_list(A) ::= TK_NUM(B) nums(C).							
								{A= new NumListNode( {C, new NumberNode(std::stoi(B))} );}
nums(A) ::= nums(B) TK_COMMA TK_NUM(C).						
								{A=new NumListNode( {B, new NumberNode(std::stoi(C))} );}
nums(A) ::= .												
								{A=nullptr;}
fp_decls(A) ::= fp_decls(B) KW_PROC TK_ID(C) opt_arg_list(D) one_more_eol variable_decls(E) block(G).
								{A= new FuncsListNode({B, new ProcedureNode(new IdNode(C), D, E, G )});}
fp_decls(A) ::= fp_decls(B) KW_FUNC TK_ID(C) opt_arg_list(D) TK_COLON primitive(E)  one_more_eol variable_decls(F) block(G).	
								{A= new FuncsListNode({B, new FunctionNode(new IdNode(C), D, E, F, G )});}
fp_decls(A) ::= .												
								{A= nullptr;}
opt_arg_list(A) ::= TK_OPEN_PAR arg_list(B) TK_CLOSE_PAR.
								{A= B;}
opt_arg_list(A) ::= .
								{A= nullptr;}
arg_list(A) ::= primitive(B) TK_ID(C) args(D).
								{A= new ArgListNode({B, new IdNode(C), D});}
arg_list(A) ::= .
								{A=nullptr;}
args(A) ::= args(B) TK_COMMA primitive(C) TK_ID(D).
								{A= new ArgListNode({C, new IdNode(D), B});}
args(A) ::= .							
								{A= nullptr;}
block(A) ::=  KW_INICIO opt_eol  statement_list(C) KW_FIN opt_eol.
								{A= new BlockNode(C);}
opt_eol ::= opt_eol TK_NEW_LINE.
								{}
opt_eol ::= .
								{}
variable_decls(A) ::= variable_decls(B) primitive(C) id_list(D) one_more_eol.
								{A= new VariableDeclListNode({B, C, D});}
variable_decls(A) ::= variable_decls(B) primitive(C) TK_OPEN_BRACK TK_NUM(D) TK_CLOSE_BRACK id_list(E) one_more_eol.	
								{A= new VariableDeclListNode({B, C, new NumberNode(std::stoi(D)), E} );}
variable_decls(A) ::= .
								{A= nullptr;}
statement_list(A) ::= statement_list(B) statement(C) one_more_eol.
								{A= new StatementListNode({B, C});}
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
if_statement(A) ::= KW_SI expr(B) KW_ENTONCES TK_NEW_LINE statement_list(C) else_statement(D) KW_FIN KW_SI.
								{A= new IfStatementNode(B, C, D);}
else_statement(A) ::= KW_SINO TK_NEW_LINE statement_list(B).
								{A= new ElseStatementNode(B);}
else_statement(A) ::= .									
								{A= nullptr;}
for_statement(A) ::= KW_PARA assignment(B) KW_HASTA expr(C) KW_HAGA.	
								{A= new ForStatementNode(B, C);}
function_call(A) ::= KW_LLAMAR TK_ID(B) opt_params(C).
								{A= new FuncCallNode(new IdNode(B), C);}
opt_params(A) ::= TK_OPEN_PAR expr_list(C) TK_CLOSE_PAR.
								{A= C;}
opt_params(A) ::= .
								{A= nullptr;}
expr_list(A) ::= expr(B) exprs(C).
								{A= new ExprListNode({C, B});}
expr_list(A) ::= .
								{A= nullptr;}
exprs(A) ::= exprs(B) TK_COMMA expr(C).
								{A= new ExprListNode({B, C});}
exprs(A) ::= .
								{A= nullptr;}
left_val(A) ::= TK_ID(B).
								{A= new IdNode(B);}
left_val(A) ::= TK_ID(B) TK_OPEN_BRACK expr(C) TK_CLOSE_BRACK.
								{A= new ArrayAccessNode(new IdNode(B), C);}
function_use(A) ::= TK_ID(B) TK_OPEN_PAR opt_params(C) TK_CLOSE_PAR.
								{A= new FunctionUseNode(new IdNode(B), C);}
constant(A) ::= bool_const(B).
								{A= B;}
constant(A) ::= TK_NUM(B).
								{A= new NumberNode(std::stoi(B));}
constant(A) ::= TK_CHAR(B).
								{A= new CharacterNode(*B);}
bool_const(A) ::= KW_VERD(B).
								{A= new BooleanNode(strncmp(B,"verdadero",9) == 0);}
bool_const(A) ::= KW_FALSO(B).
								{A= new BooleanNode(strncmp(B,"falso",5) != 0);}
assignment(A) ::= left_val(B) TK_ARROW expr(C).
								{A= new AssignmentNode(B, C);}
return_statement(A) ::= KW_RETORNE expr(B).
								{A= new ReturnNode(B);}
expr(A) ::= expr(B) TK_MENOR_Q term0(C).
								{A= new LessThanNode(B, C);}
expr(A) ::= expr(B) TK_MAYOR_Q term0(C).
								{A= new GrtrThanNode(B, C);}
expr(A) ::= expr(B) TK_MAYOR_Q_IG term0(C).
								{A= new GrtrThanEtNode(B, C);}
expr(A) ::= expr(B) TK_MENOR_Q_IG term0(C).
								{A= new LessThanEtNode(B, C);}
expr(A) ::= expr(B) TK_IGUAL_Q term0(C).
								{A= new EqualsNode(B, C);}
expr(A) ::= term0(B).				
								{A= B;}
term0(A) ::= term0(B) TK_SUMA term1(C).
								{A= new AdditionNode(B, C);}
term0(A) ::= term0(B) TK_RESTA term1(C).	
								{A= new SubtractionNode(B, C);}
term0(A) ::= term0(B) TK_O term1(C).	
								{A= new OrNode(B, C);}
term0(A) ::= term1(B).		
								{A= B;}
term1(A) ::= term1(B) TK_MULT final(C).
								{A= new MultiplicationNode(B, C);}
term1(A) ::= term1(B) TK_DIV final(C).
								{A= new DivisionNode(B, C);}
term1(A) ::= term1(B) TK_PODER final(C).
								{A= new ExponentNode(B, C);}
term1(A) ::= term1(B) TK_Y final(C).
								{A= new AndNode(B,C);}
term1(A) ::= term1(B) TK_MOD final(C).
								{A= new ModulusNode(B, C);}
term1(A) ::= final(B).
								{A= B;}
final(A) ::= left_val(B).	
								{A= B;}
final(A) ::= function_use(B).
								{A= B;}
final(A) ::= constant(B).
								{A= B;}
final(A) ::= TK_OPEN_PAR expr(B) TK_CLOSE_PAR.
								{A= B;}