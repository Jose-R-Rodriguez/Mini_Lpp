#include "ast.hpp"
std::string IdListNode::toString(){
	std::string result= "";
	for (Node * child : child_list){
		if (child != nullptr){
			result+= child->toString();
		}
	}
	return result;
}

std::string IdNode::toString(){
	std::cout<<value<<std::endl;
	return value;
}

std::string NumberNode::toString(){
	return std::to_string(value);
}

std::string NumListNode::toString(){
	std::string result= "";
	for (Node * child : child_list){
		if (child != nullptr){
			result+= child->toString();
		}
	}
	return result;
}

std::string VariableDeclListNode::toString(){
	std::string result= "";
	for (Node * child : child_list){
		if (child != nullptr){
			result+= child->toString();
		}
	}
	return result;
}

std::string IntDeclNode::toString(){
	return "entero";
}
std::string CharDeclNode::toString(){
	return "caracter";
}
std::string BooleanDeclNode::toString(){
	return "booleano";
}