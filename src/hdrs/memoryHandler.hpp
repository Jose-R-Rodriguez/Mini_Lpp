#ifndef MEMORYMANAGEMENT_HPP
#define MEMORYMANAGEMENT_HPP
#include <unordered_map>
#include "common.hpp"
class MemoryHandler {
public:
	MemoryHandler();
	std::string allocate4BytePrimitive(int);
	std::string allocateString(const std::string&, const std::string type= "$str");
	std::string generateDataCode();
	std::string allocateInt(const int&, const std::string type= "$numb");
private:
	std::string getStringPreambles();
	std::string getIntPreambles();
	int constCount, tempCount, stringCount, numberCount;
	std::unordered_map<int, std::string>inMemoryInts;
	std::unordered_map<std::string, std::string>inMemoryStrings;
};
#endif