#include "Hero.h" 
#include <fstream>
#include <cmath>
#include "JSON.h"
#include <exception>


Hero Hero::parse(const std::string& unitfilename){
	//Istream
	std::ifstream inputunit;
	inputunit.open(unitfilename);
	if (inputunit.fail())
	{
		throw JSON::ParseException("Couldn't open file,the file doesn't exist.");
	}
	JSON values = JSON::parseFromIstream(inputunit);
	inputunit.close();
	//File
	//std::map<std::string,std::string> values=JsonParser::ParseFile(unitfilename);
	return Hero(values.get<std::string>("name"),values.get<int>("base_health_points"), values.get<int>("base_damage"),values.get<float>("base_attack_cooldown"));
}