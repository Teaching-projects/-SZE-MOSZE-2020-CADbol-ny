#include "units.h"
#include <fstream>
#include <cmath>
#include "JSON.h"
#include <exception>


Unit::Unit(const std::string& name, int hp, int damage, float attackCooldown) :m_name(name), m_hp(hp), m_damage(damage), m_attackCooldown(attackCooldown) {}

Unit Unit::parse(const std::string& unitfilename){
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
	return Unit(values.get<std::string>("name"),values.get<int>("hp"), values.get<int>("dmg"),values.get<float>("attackcooldown"));
}
