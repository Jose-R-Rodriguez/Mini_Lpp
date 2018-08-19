#ifndef LEXER_HPP
#define LEXER_HPP
#include <istream>
#include <map>
#include <unordered_map>
#include <algorithm>
#include "common.hpp"
#include "parser.hpp"

enum Token{
	TK_STR_LIT=		3,
	TK_ID=			4,
	TK_NEW_LINE=	5
};

class Lexer{
public:
	Lexer (std::istream& input);
	int ResolveToken(){ return _ResolveToken(myscanner); }
private:
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
			size_t h= 0;
			for (int letter= 0; letter < Key.length(); ++letter){
				h+=toupper(Key[letter]);
			}
			return h;
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
	using CaseInsensitiveMap = std::map<std::string, int, CaseInsensitiveComparator>;
	using CaseIUnorderedMap= std::unordered_map<std::string, int, CaseInsensitiveComparator>;
	int _ResolveToken(void*);
	std::istream& input;
	void* myscanner;
	~Lexer();
	CaseInsensitiveMap Keywords{
		{"inxO",	1}
	};
};
#endif