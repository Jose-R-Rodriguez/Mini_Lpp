#ifndef MEMORYMANAGEMENT_HPP
#define MEMORYMANAGEMENT_HPP
#include <unordered_map>
#include "common.hpp"
class MemoryHandler {
public:
	MemoryHandler();
	std::string allocate4BytePrimitive(int);
	std::string allocateString(const std::string&);
	std::string generateDataCode();
private:
	int constCount, tempCount, stringCount;
	std::unordered_map<std::string, int>inMemoryInts;
	std::unordered_map<std::string, std::string>inMemoryStrings;
};
#endif