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

struct CaseInsensitiveComparator{
	bool operator()(const std::string& str1, const std::string& str2) const {
		std::string temp1(str1.length(), ' '), temp2(str2.length(), ' ');
		std::transform(str1.begin(), str1.end(), temp1.begin(), toupper);
		std::transform(str2.begin(), str2.end(), temp2.begin(), toupper);
		//std::cout<<"COMPARING "<<temp1<<" TO "<<temp2<<": "<<(temp1==temp2)<<std::endl;
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
class Lexer{
public:
	Lexer (std::istream& input);
	int ResolveToken(){ return _ResolveToken(myscanner); }
	std::string getLexeme() { return currentLexeme; }
	void setLexeme(std::string lexeme) { currentLexeme= lexeme; }
private:
	using CaseInsensitiveMap = std::map<std::string, int, CaseInsensitiveComparator>;
	using CaseIUnorderedMap= std::unordered_map<std::string, int, CaseIHash, CaseIPredicate>;
	int _ResolveToken(void*);
	std::istream& input;
	void* myscanner;
	std::string currentLexeme;
	~Lexer();
	CaseIUnorderedMap Keywords{
		{"inicio",			KW_INICIO},
		{"fin",				KW_FIN},
		{"entonces",		KW_ENTONCES},
		{"si",				KW_SI},
		{"escriba",			109},
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
		{"<-",				TK_ARROW}
	};
};
#endif