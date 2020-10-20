#include "units.h"
#include "jsonparser.h"
#include <exception>

Unit::Unit(std::string name, int hp, int damage) :m_name(name), m_hp(hp), m_damage(damage) {}

void Unit::dealDamageTo(Unit& damagedUnit){
	damagedUnit.m_hp = damagedUnit.getHp() - this->getDamage() < 0 ? 0 : damagedUnit.getHp() - this->getDamage();
}

Unit* Unit::parseUnit(const std::string& unitfilename){
	//Istream
	std::ifstream inputunit;
	inputunit.open(unitfilename);
	if (inputunit.fail())
	{
		throw std::exception("Couldn't open file,the file doesn't exist.");
	}
	std::map<std::string, std::string> values = JsonParser::ParseIstream(inputunit);
	inputunit.close();
	//File
	//std::map<std::string,std::string> values=JsonParser::ParseFile(unitfilename);
	Unit* unit=new Unit(values["name"],std::stoi(values["hp"]), std::stoi(values["dmg"]));
	return unit;
}
