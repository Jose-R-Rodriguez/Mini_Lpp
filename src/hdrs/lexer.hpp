#ifndef LEXER_HPP
#define LEXER_HPP
#include <istream>
#include <map>
#include <unordered_map>
#include <algorithm>
#include "common.hpp"
#include "parser.hpp"


enum Token {
	TK_STR_LIT= 255
};

static const size_t SIZE = 1024;


struct CaseInsensitiveComparator{
	bool operator()(const std::string& str1, const std::string& str2) const {
		std::string temp1(str1.length(), ' '), temp2(str2.length(), ' ');
		std::transform(str1.begin(), str1.end(), temp1.begin(), toupper);
		std::transform(str2.begin(), str2.end(), temp2.begin(), toupper);
		return (temp1 < temp2);
	}
};
struct CaseIHash{
	size_t operator()(const std::string& Key) const {
		size_t hash= 0;
		for (int letter= 0; letter < Key.length(); ++letter){
			hash+=toupper(Key[letter]);
		}
		return hash;
	};
};
struct CaseIPredicate{
	bool operator()(const std::string& Left, const std::string& Right) const{
		return Left.size() == Right.size() 
			&& std::equal ( Left.begin() , Left.end() , Right.begin() ,[]( char a , char b ){
				return toupper(a) == toupper(b); 
			}
		);
	}
};
struct input_t {
    char *buf;
    char *lim;
    char *cur;
	char *mar;
    char *tok;
    bool eof;
	std::istream& in;

    input_t(std::istream& in);
    bool fill(size_t need);
    
};
extern unsigned int currentLine;
class Lexer{
public:
	Lexer(std::istream& input) : in(input){};
	std::string getLexeme() { return lexeme; }
	void setLexeme(std::string lexeme) { this->lexeme= lexeme; }
	int lex ();
private:
	using CaseInsensitiveMap = std::map<std::string, int, CaseInsensitiveComparator>;
	using CaseIUnorderedMap= std::unordered_map<std::string, int, CaseIHash, CaseIPredicate>;
	struct input_t in;
	std::string lexeme;
	void* myscanner;
	CaseIUnorderedMap Keywords{
		{"inicio",			KW_INICIO},
		{"fin",				KW_FIN},
		{"entonces",		KW_ENTONCES},
		{"si",				KW_SI},
		//{"escriba",			KW_ESCRIBA},
		//{"var",				KW_VAR}
		{"tipo",			KW_TIPO},
		{"es",				KW_ES},
		{"de",				KW_DE},
		{"arreglo",			KW_ARREGLO},
		{"entero",			KW_ENTERO},
		{"booleano",		KW_BOOLEANO},
		{"caracter",		KW_CARACTER},
		{"procedimiento",	KW_PROC},
		{"FUNCION",			KW_FUNC},
		{"sino",			KW_SINO},
		{"para",			KW_PARA},
		{"HASTA",			KW_HASTA},
		{"haga",			KW_HAGA},
		{"llamar",			KW_LLAMAR},
		{"verdadero",		KW_VERD},
		{"false",			KW_FALSO},
		{"retorn",			KW_RETORNE},
		{"mod",				TK_MOD},
		{"div",				TK_DIV},
		{"y",				TK_Y},
		{"O",				TK_O},
		//{"mientras",		KW_MIENTRAS},
		//{"repita",			KW_REPITA},
		
	};
};
#endif