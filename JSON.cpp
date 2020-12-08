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
	std::map<std::string, std::variant<std::string,int,float>> unit;
	std::string line, key, value;
	bool floate;
	unsigned int i;
	while (parsed) {
		std::getline(parsed, line);
		if (line.size() > 2) {
			i = 0;
			if (line.find('[') != std::string::npos && line.find(']') != std::string::npos)
			{
				key = "", value = "";
				while (line[i] == '\"' || line[i] == ' ' || line[i] == '{') {
					i++;
				}
				while (line[i] != '\"' && (line[i] != ' ' && line[i + 1] != ' ')) {
					key += line[i];
					i++;
				}
				i++;
				while (line[i] == ' ' || line[i] == ':' || line[i] == '[' || line[i] == '\"') {
					i++;
				}
				while (line[i] != '\"')
				{
					value += line[i];
					i++;
				}
				unit.insert({ key, value });
			}
			else if (line.find('[') != std::string::npos && line.find(']') == std::string::npos)
			{
				std::string slist="";
				key = "";
				while (line[i] == '\"' || line[i] == ' ' || line[i] == '{') {
					i++;
				}
				while (line[i] != '\"' && (line[i] != ' ' && line[i + 1] != ' ')) {
					key += line[i];
					i++;
				}
				while (line.find(']') == std::string::npos)
				{
					value = "",i=0;
					std::getline(parsed, line);
					if (line.find(']') == std::string::npos)
					{
						while (line[i] == ' ' || line[i] == '\"')
						{
							i++;
						}
						while (line[i] != '\"')
						{
							value += line[i];
							i++;
						}
						slist+=value+'\r';
					}
				}
				unit.insert({ key, slist });
			}
			else {
				while (i < line.size() - 2) {
					floate = false;
					key = "", value = "";
					while (line[i] == '\"' || line[i] == ' ' || line[i] == '{') {
						i++;
					}
					while (line[i] != '\"' && (line[i] != ' ' && line[i + 1] != ' ')) {
						key += line[i];
						i++;
					}
					i++;
					while (line[i] == ' ' || line[i] == ':') {
						i++;
					}
					if (line[i] == '\"') {
						i++;
						while (line[i] != '\"' && line[i] != '\r' && line[i] != '\n') {
							value += line[i];
							i++;
						}
						unit.insert({ key,value });
					}
					else
					{
						while (line[i] != '\r' && line[i] != ',' && line[i] != '\n' && i < line.size()) {
							value += line[i];
							if (line[i] == '.')
							{
								floate = true;
							}
							i++;
						}
						if (floate) {
							unit.insert({ key,std::stof(value) });
						}
						else {
							unit.insert({ key,std::stoi(value) });
						}
					}
					if (line.find(',') != std::string::npos) {
						while (i < line.size() && line[i] != ',') {
							i++;
						}
						i++;
					}
				}
			}
		}
	}
	return JSON(unit);
}




