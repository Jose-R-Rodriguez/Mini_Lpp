#include "memoryHandler.hpp"

MemoryHandler::MemoryHandler() : constCount(0), tempCount(0), stringCount(0), numberCount(0), lblCount(0)
{}

std::string MemoryHandler::allocateString(const std::string& newString, const std::string type){
	const auto& str_map_it= inMemoryStrings.find(newString);
	if ( str_map_it != inMemoryStrings.end()){
		return str_map_it->second;
	}
	std::ostringstream place;
	place<<type
		<< ((type=="$temp") ? ++tempCount:++stringCount);
	std::string placeString= place.str();
	inMemoryStrings.emplace(newString, placeString);
	return placeString;
}

std::string MemoryHandler::generateDataCode(){
	std::ostringstream result;
	result<<"section .data"<<std::endl
		<<getStringPreambles()
		<<getIntPreambles()
		<<getVariablePreambles();
	return result.str();
}

std::string MemoryHandler::getStringPreambles(){
	std::ostringstream result;
	for (auto &str : inMemoryStrings){
		result<<str.second<<" db \""<<str.first<<"\", 0"<<std::endl;
	}
	return result.str();
}

std::string MemoryHandler::getIntPreambles(){
	std::ostringstream result;
	for (auto &integ : inMemoryInts){
		result<<integ.second<<" dd "<<integ.first<<std::endl;
	}
	return result.str();
}

std::string MemoryHandler::getVariablePreambles(){
	std::ostringstream result;
	for (auto &var : inMemoryVariables){
		result<<var.first<<" dd "<<0<<std::endl;
	}
	return result.str();
}

std::string MemoryHandler::allocateInt(const int& newInt, const std::string type){
	const auto& str_map_it= inMemoryInts.find(newInt);
	if ( str_map_it != inMemoryInts.end()){
		return str_map_it->second;
	}
	std::ostringstream place;
	place<<type
		<< ((type=="$temp") ? ++tempCount:++numberCount);
	std::string placeString= place.str();
	inMemoryInts.emplace(newInt, placeString);
	return placeString;
}

bool MemoryHandler::allocateVariable(int type, std::string name){
	const auto& var_map_it= inMemoryVariables.find(name);
	if ( var_map_it != inMemoryVariables.end()){
		return false;
	}
	inMemoryVariables.emplace(name, type);
	return true;
}

int MemoryHandler::getVariableType(std::string name){
	const auto& var_map_it= inMemoryVariables.find(name);
	if ( var_map_it != inMemoryVariables.end()){
		return var_map_it->second;
	}
	return 0;
}

std::string MemoryHandler::getNewLabel(std::string lblName){
	std::string result= lblName + std::to_string(++lblCount);
	return result;
}