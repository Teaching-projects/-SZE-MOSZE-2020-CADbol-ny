#include "jsonparser.h"
#include <sstream>

std::map<std::string,std::string> JsonParser::ParseFile(const std::string& filename){
	std::map<std::string, std::string> unit;
	std::ifstream input;
	input.open(filename);
	if (input.fail()){
		throw 1;
	}
	unit = JsonParser::ParseIstream(input);
	input.close();
	return unit;
}

std::map< std::string, std::string> JsonParser::ParseIstream(std::ifstream& fileCont) {
	std::map<std::string, std::string> unit;
	std::string line, line1, line2;
	while (fileCont){
		line1 = "", line2 = "";
		std::getline(fileCont, line);
		if (line.find('{') == std::string::npos && line.find('}') == std::string::npos){
			for (unsigned int i = 0; i < line.find(':'); i++){
				if (line[i] != ' ' && line[i] != '"'){
					line1 += line[i];
				}
			}
			for (unsigned int i = line.find(':') + 1; i < line.size(); i++){
				if (line[i] != ' ' && line[i] != '"' && line[i] != ',' && line[i]!='\n' && line[i] !='\r'){
					line2 += line[i];
				}
			}
			unit.insert({ line1,line2 });
		}
	}
	return unit;
}
std::map< std::string, std::string> JsonParser::ParseString(std::string& text){
	std::map<std::string, std::string> unit;
	std::string line,line1 = "", line2 = "";
	std::istringstream iss(text);
	while (iss){
		line1 = "", line2 = "";
		std::getline(iss, line);
		if (line.find('{') == std::string::npos && line.find('}') == std::string::npos){
			for (unsigned int i = 0; i < line.find(':'); i++){
				if (line[i] != ' ' && line[i] != '"'){
					line1 += line[i];
				}
			}
			for (unsigned int i = line.find(':') + 1; i < line.size(); i++){
				if (line[i] != ' ' && line[i] != '"' && line[i] != ','){
					line2 += line[i];
				}
			}
			unit.insert({ line1,line2 });
		}
	}
	return unit;
}


