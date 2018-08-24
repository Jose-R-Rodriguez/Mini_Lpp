#ifndef AST_HPP
#define AST_HPP
#include "common.hpp"
#define DEFINE_BINARY_NODE(name)\
	class name##Node : public Node{\
	public:\
		name##Node(Node *left, Node* right) : left(left), right(right){}\
		Node *left;\
		Node *right;\
		std::string toString();\
	}
#define DEFINE_PRIMITIVE_NODE(name, type)\
	class name##Node : public Node{\
		public:\
		name##Node(type value): value(value){}\
		type value;\
		std::string toString();\
	}
class Node {
public:
	virtual std::string toString()=0;
	virtual ~Node(){}
};
DEFINE_BINARY_NODE(ADD);
DEFINE_PRIMITIVE_NODE(Number, int);
DEFINE_PRIMITIVE_NODE(Character, char);
DEFINE_PRIMITIVE_NODE(Boolean, bool);
#endif