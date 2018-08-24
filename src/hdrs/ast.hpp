#ifndef AST_HPP
#define AST_HPP
#include "common.hpp"
#include <deque>
#define DEFINE_N_ARY_NODE(name)\
	class name##Node : public Node{\
	public:\
		template<typename Child>\
		name##Node(Child&& child){\
			child_list.push_back(std::move(child));\
		}\
		template<typename FirstChild, typename... Children>\
		name##Node(FirstChild&& f, Children&& ... args) : name##Node(args...){\
			child_list.push_front(std::move(f));\
		}\
		std::deque<Node*> child_list;\
		std::string toString();\
	}
#define DEFINE_PRIMITIVE_NODE(name, type)\
	class name##Node : public Node{\
	public:\
		name##Node(type value): value(value){}\
		name##Node(){}\
		type value;\
		std::string toString();\
	}
class Node {
public:
	virtual std::string toString()=0;
	virtual ~Node(){}
};
DEFINE_N_ARY_NODE(Add);
DEFINE_N_ARY_NODE(IntDeclaration);
DEFINE_N_ARY_NODE(IdList);
DEFINE_N_ARY_NODE(Typedef);
DEFINE_N_ARY_NODE(NumList);
DEFINE_N_ARY_NODE(VariableDeclList);

DEFINE_PRIMITIVE_NODE(Number, int);
DEFINE_PRIMITIVE_NODE(Character, char);
DEFINE_PRIMITIVE_NODE(Boolean, bool);
DEFINE_PRIMITIVE_NODE(Id, std::string);
DEFINE_PRIMITIVE_NODE(IntDecl, void*);
DEFINE_PRIMITIVE_NODE(BooleanDecl, void*);
DEFINE_PRIMITIVE_NODE(CharDecl, void*);
#endif