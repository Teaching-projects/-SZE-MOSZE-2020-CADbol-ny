#include "Monster.h" 
#include <fstream>
#include <cmath>
#include "JSON.h"
#include <exception>


Monster Monster::parse(const std::string& unitfilename){
	//Istream
	std::ifstream inputunit;
	inputunit.open(unitfilename);
	if (inputunit.fail())
	{
		throw JSON::ParseException("Couldn't open file,the file doesn't exist.");
	}
	std::map<std::string, std::string> values = JSON::parseFromIstream(inputunit);
	inputunit.close();
	//File
	//std::map<std::string,std::string> values=JsonParser::ParseFile(unitfilename);
	return Monster(values["name"],std::stoi(values["hp"]), std::stoi(values["dmg"]),std::stof(values["attackcooldown"]));
}