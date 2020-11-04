#include "JSON.h"
#include <sstream>

JSON JSON::parseFromFile(const std::string& unitfile){
	JSON unitmap;
	std::ifstream inputunit;
	inputunit.open(unitfile);
	if (inputunit.fail()){
		throw ParseException("Couldn't open file,the file doesn't exist.");
	}
	unitmap = JSON::parseFromIstream(inputunit);
	inputunit.close();
	return unitmap;
}
JSON JSON::parseFromIstream(std::ifstream& inputunit) {
	return JSON::parse(inputunit);
}
JSON JSON::parseFromString(std::string& text){
	std::istringstream iss(text);
	return JSON::parse(iss);
}
template<typename T>
JSON JSON::parse(T& parsed)
{
	JSON unit;
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

template<typename T>
T& JSON::get(const std::string& key)
{
	return this->at(key);
}



