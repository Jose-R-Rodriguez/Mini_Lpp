#include "ast.hpp"
std::string IdListNode::toString(){
	std::string result= "";
	for (int x= 0; x<child_list.size(); ++x){
		if (child_list[x]){
			result+= child_list[x]->toString();
		}
		if (x == 0){
			result+= ",";
		}
	}
	return result;
}

std::string IdNode::toString(){
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
	if (child_list.size() == 3){
		for (int x= 0 ; x<child_list.size(); x+=3){
			if (child_list[x])
				result+= child_list[x]->toString()+"\n";
			result+= child_list[x+1]->toString() + " ";
			result+= child_list[x+2]->toString();
		};
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

std::string ArgListNode::toString(){
	std::string result= "";
	for (int x= 0 ; x<child_list.size(); x+=3){
		if (child_list[x])
			result+= child_list[x]->toString() + ", ";
		result+= child_list[x+1]->toString() + " ";
		result+= child_list[x+2]->toString();
	};
	return result;
}

std::string FuncsListNode::toString(){
	std::string result= "\n";
	for (Node * child : child_list){
		if (child != nullptr){
			result+= child->toString();
		}
	}
	result+="\n";
	return result;
}

std::string ProcedureNode::toString(){
	std::string result= "procedimiento ";
	for (int x = 0; x<child_list.size(); ++x){
		switch (x){
			case 1:
				result+= " (";
				break;
			case 2:
				result+= ")\n";
				break;
			case 3:
				result+= "\n";
				break;
		}
		if (child_list[x]){
			result +=  child_list[x]->toString();
		}
	}
	return result;
}

std::string BlockNode::toString(){
	std::string result= "\ninicio \n";
	for (Node * child : child_list){
		if (child != nullptr){
			result+= child->toString();
		}
	}
	result += "\nfin \n";
	return result;
}

std::string FunctionNode::toString(){
	std::string result= "funcion ";
	for (int x = 0; x<child_list.size(); ++x){
		switch (x){
			case 1:
				result+= " (";
				break;
			case 2:
				result+= " ) : ";
				break;
			case 3:
				result+= "\n";
				break;
		}
		if (child_list[x]){
			result +=  child_list[x]->toString();
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
	std::string result= "si (";
	result+= child_list[0]->toString() + ")\nentonces\n";
	if (child_list[1])
		result+= child_list[1]->toString();
	if (child_list[2])
		result+= child_list[2]->toString();
	result+= "fin si\n";
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
	std::string result= "sino \n";
	if (child_list[0])
		result+= child_list[0]->toString();
	return result;
}

std::string StatementListNode::toString(){
	std::string result= "";
	for (Node * child : child_list){
		if (child != nullptr){
			result+= child->toString() +"\n";
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
	result+= child_list[0]->toString() + " = " + child_list[1]->toString();
	return result;
}

std::string ReturnNode::toString(){
	std::string result= " retorne";
	result += child_list[0]->toString();
	return result;
}

std::string ModulusNode::toString(){
	std::string result= "";
	result+= child_list[0]->toString() + " % " + child_list[1]->toString();
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
	result+= child_list[0]->toString() + " + " + child_list[1]->toString();
	return result;
}

std::string SubtractionNode::toString(){
	std::string result= "";
	result+= child_list[0]->toString() + " - " + child_list[1]->toString();
	return result;
}

std::string MultiplicationNode::toString(){
	std::string result= "";
	result+= child_list[0]->toString() + " * " + child_list[1]->toString();
	return result;
}

std::string DivisionNode::toString(){
	std::string result= "";
	result+= child_list[0]->toString() + " / " + child_list[1]->toString();
	return result;
}

std::string AssignmentNode::toString(){
	std::string result= "";
	result+= child_list[0]->toString() + "<-";
	result+= child_list[1]->toString();
	return result;
}

std::string ExponentNode::toString(){
	std::string result= "";
	result+= child_list[0]->toString() + " ^ " + child_list[1]->toString();
	return result;
}

std::string OrNode::toString(){
	std::string result= "";
	result+= child_list[0]->toString() + " | " + child_list[1]->toString();
	return result;
}

std::string AndNode::toString(){
	std::string result= "";
	result+= child_list[0]->toString() + " & " + child_list[1]->toString();
	return result;
}

std::string LessThanNode::toString(){
	std::string result= "";
	result+= child_list[0]->toString() + " < " + child_list[1]->toString();
	return result;
}

std::string GrtrThanEtNode::toString(){
	std::string result= "";
	result+= child_list[0]->toString() + " >= " + child_list[1]->toString();
	return result;
}

std::string GrtrThanNode::toString(){
	std::string result= "";
	result+= child_list[0]->toString() + " > " + child_list[1]->toString();
	return result;
}

std::string LessThanEtNode::toString(){
	std::string result= "";
	result+= child_list[0]->toString() + " <= " + child_list[1]->toString();
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