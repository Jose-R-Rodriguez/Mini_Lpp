#include "memoryHandler.hpp"

MemoryHandler::MemoryHandler() : constCount(0), tempCount(0), stringCount(0), numberCount(0){}

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
		<<getIntPreambles();
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
