#include "JSON.h"
#include <sstream>

JSON JSON::parseFromFile(const std::string& unitfile){
	std::ifstream inputunit;
	inputunit.open(unitfile);
	if (inputunit.fail()){
		throw ParseException("Couldn't open file,the file doesn't exist.");
	}
	JSON unitmap = JSON::parseFromIstream(inputunit);
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
	std::map<std::string, std::any> unit;
	std::string line, key, value;
	bool floate;
	unsigned int i;
	while (parsed) {
		i = 0;
		std::getline(parsed, line);
		if (line.size()>2) {
		while (i<line.size()-2) {
			floate=false;
			key = "", value = "";
			while (line[i] == '\"' || line[i] == ' ' || line[i]=='{') {
				i++;
			}
			while (line[i] != '\"' && (line[i] != ' ' && line[i + 1] != ' ')) {
				key += line[i];
				i++;
			}
			i++;
			while (line[i] == ' ' || line[i] == ':'){
				i++;
			}
			if (line[i] == '\"'){
				i++;
				while (line[i] != '\"' && line[i]!='\r' && line[i]!='\n'){
					value += line[i];
					i++;
				}
				unit.insert({ key,value });
			}
			else
			{
				while (line[i] != '\r' && line[i] != ',' && line[i] != '\n' && i < line.size()){
					value += line[i];
					if (line[i] == '.')
					{
						floate = true;
					}
					i++;
				}
				if (floate){
					unit.insert({ key,std::stof(value) });
				}
				else{
					unit.insert({ key,std::stoi(value) });
				}
			}
			if (line.find(',') != std::string::npos){
				while (line[i] != ',' && i < line.size()) {
					i++;
				}
				i++;
			}
		}
		}
	}
	return JSON(unit);
}




