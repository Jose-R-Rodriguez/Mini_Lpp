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
	std::cout<<"Printing out variable decl list"<<std::endl;
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

std::string ArgListNode::toString(){
	std::string result= "";
	for (Node * child : child_list){
		if (child != nullptr){
			result+= child->toString();
		}
	}
	return result;
}

std::string FuncsListNode::toString(){
	std::string result= "";
	for (Node * child : child_list){
		if (child != nullptr){
			result+= child->toString();
		}
	}
	return result;
}

std::string ProcedureNode::toString(){
	std::string result= "";
	for (Node * child : child_list){
		if (child != nullptr){
			result+= child->toString();
		}
	}
	return result;
}

std::string BlockNode::toString(){
	std::string result= "inicio \n";
	for (Node * child : child_list){
		if (child != nullptr){
			result+= child->toString();
		}
	}
	result += "\nfin \n";
	return result;
}

std::string FunctionNode::toString(){
	std::string result= "";
	for (Node * child : child_list){
		if (child != nullptr){
			result+= child->toString();
		}
	}
	return result;
}

std::string FuncCallNode::toString(){
	std::string result= "";
	for (Node * child : child_list){
		if (child != nullptr){
			result+= child->toString();
		}
	}
	return result;
}

std::string IfStatementNode::toString(){
	std::string result= "";
	for (Node * child : child_list){
		if (child != nullptr){
			result+= child->toString();
		}
	}
	return result;
}

std::string ForStatementNode::toString(){
	std::string result= "";
	for (Node * child : child_list){
		if (child != nullptr){
			result+= child->toString();
		}
	}
	return result;
}

std::string ElseStatementNode::toString(){
	std::string result= "";
	for (Node * child : child_list){
		if (child != nullptr){
			result+= child->toString();
		}
	}
	return result;
}

std::string StatementListNode::toString(){
	std::string result= "";
	for (Node * child : child_list){
		if (child != nullptr){
			result+= child->toString();
		}
	}
	return result;
}

std::string BooleanNode::toString(){
	return (value) ? "verdadero" : "falso";
}

std::string CharacterNode::toString(){
	return std::string(value, 1);
}

std::string ParamListNode::toString(){
	std::string result= "";
	for (Node * child : child_list){
		if (child != nullptr){
			result+= child->toString();
		}
	}
	return result;
}


std::string ArrayAccessNode::toString(){
	std::string result= "";
	for (Node * child : child_list){
		if (child != nullptr){
			result+= child->toString();
		}
	}
	return result;
}

std::string FunctionUseNode::toString(){
	std::string result= "";
	for (Node * child : child_list){
		if (child != nullptr){
			result+= child->toString();
		}
	}
	return result;
}

std::string EqualsNode::toString(){
	std::string result= "";
	for (Node * child : child_list){
		if (child != nullptr){
			result+= child->toString();
		}
	}
	return result;
}

std::string ReturnNode::toString(){
	std::string result= "";
	for (Node * child : child_list){
		if (child != nullptr){
			result+= child->toString();
		}
	}
	return result;
}

std::string ModulusNode::toString(){
	std::string result= "";
	for (Node * child : child_list){
		if (child != nullptr){
			result+= child->toString();
		}
	}
	return result;
}

std::string TypedefNode::toString(){
	std::string result= "";
	for (Node * child : child_list){
		if (child != nullptr){
			result+= child->toString();
		}
	}
	return result;
}

std::string AdditionNode::toString(){
	std::string result= "";
	for (Node * child : child_list){
		if (child != nullptr){
			result+= child->toString();
		}
	}
	return result;
}

std::string SubtractionNode::toString(){
	std::string result= "";
	for (Node * child : child_list){
		if (child != nullptr){
			result+= child->toString();
		}
	}
	return result;
}

std::string MultiplicationNode::toString(){
	std::string result= "";
	for (Node * child : child_list){
		if (child != nullptr){
			result+= child->toString();
		}
	}
	return result;
}

std::string DivisionNode::toString(){
	std::string result= "";
	for (Node * child : child_list){
		if (child != nullptr){
			result+= child->toString();
		}
	}
	return result;
}

std::string AssignmentNode::toString(){
	std::string result= "";
	for (Node * child : child_list){
		if (child != nullptr){
			result+= child->toString();
		}
	}
	return result;
}

std::string ExponentNode::toString(){
	std::string result= "";
	for (Node * child : child_list){
		if (child != nullptr){
			result+= child->toString();
		}
	}
	return result;
}

std::string OrNode::toString(){
	std::string result= "";
	for (Node * child : child_list){
		if (child != nullptr){
			result+= child->toString();
		}
	}
	return result;
}

std::string AndNode::toString(){
	std::string result= "";
	for (Node * child : child_list){
		if (child != nullptr){
			result+= child->toString();
		}
	}
	return result;
}

std::string LessThanNode::toString(){
	std::string result= "";
	for (Node * child : child_list){
		if (child != nullptr){
			result+= child->toString();
		}
	}
	return result;
}

std::string GrtrThanEtNode::toString(){
	std::string result= "";
	for (Node * child : child_list){
		if (child != nullptr){
			result+= child->toString();
		}
	}
	return result;
}

std::string GrtrThanNode::toString(){
	std::string result= "";
	for (Node * child : child_list){
		if (child != nullptr){
			result+= child->toString();
		}
	}
	return result;
}

std::string LessThanEtNode::toString(){
	std::string result= "";
	for (Node * child : child_list){
		if (child != nullptr){
			result+= child->toString();
		}
	}
	return result;
}

std::string TypedefArrayNode::toString(){
	std::string result= "";
	for (Node * child : child_list){
		if (child != nullptr){
			result+= child->toString();
		}
	}
	return result;
}