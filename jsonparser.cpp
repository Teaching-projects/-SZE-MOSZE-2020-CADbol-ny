#include "jsonparser.h"
#include <sstream>
#include <exception>

std::map<std::string,std::string> JsonParser::ParseFile(const std::string& unitfile){
	std::map<std::string, std::string> unitmap;
	std::ifstream inputunit;
	inputunit.open(unitfile);
	if (inputunit.fail()){
		throw std::runtime_error("Couldn't open file,the file doesn't exist.");
	}
	unitmap = JsonParser::ParseIstream(inputunit);
	inputunit.close();
	return unitmap;
}
std::map< std::string, std::string> JsonParser::ParseIstream(std::ifstream& inputunit) {
	return JsonParser::Parser(inputunit);
}
std::map< std::string, std::string> JsonParser::ParseString(std::string& text){
	std::istringstream iss(text);
	return JsonParser::Parser(iss);
}
template<typename T>
std::map< std::string, std::string> JsonParser::Parser(T& parsed)
{
	std::map<std::string, std::string> unit;
	std::string line, key, value;
	unsigned int i = 0;
	while (parsed){
		key = "", value = "", i = 0;
		std::getline(parsed, line);
		if (line.find('{') == std::string::npos && line.find('}') == std::string::npos) {
			while (line[i] == ' ' || line[i] == ',' || line[i] == ':' || line[i] == '\n' || line[i] == '\r' || line[i] == '\"') {
				i++;
			}
			while (line[i] != ' ' && line[i] != ',' && line[i] != ':' && line[i] != '\n' && line[i] != '\r' && line[i] != '\"') {
				key += line[i];
				i++;
			}
			for (unsigned int j = i + 1; j < line.size(); j++) {
				if (line[j] != ' ' && line[j] != ',' && line[j] != ':' && line[j] != '\n' && line[j] != '\r' && line[j] != '\"') {
					value += line[j];
				}
			}
			unit.insert({ key,value });
		}
	}
	return unit;
}



