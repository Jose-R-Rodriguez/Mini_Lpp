#include "memoryHandler.hpp"

MemoryHandler::MemoryHandler() : constCount(0), tempCount(0), stringCount(0){}

std::string MemoryHandler::allocateString(const std::string& newString){
	const auto& str_map_it= inMemoryStrings.find(newString);
	if ( str_map_it != inMemoryStrings.end()){
		return str_map_it->second;
	}
	std::ostringstream place;
	place<<"str"<<++stringCount;
	std::string placeString= place.str();
	inMemoryStrings.emplace(newString, placeString);
	return placeString;
}