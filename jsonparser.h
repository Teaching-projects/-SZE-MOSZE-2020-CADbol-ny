#pragma once
#include <map>
#include <string>
#include <fstream>

class JsonParser {
public:
	static std::map< std::string, std::string> ParseFile(const std::string&);

	static std::map< std::string, std::string> ParseIstream(std::ifstream&);

	static std::map< std::string, std::string> ParseString(std::string& fileCont);
};