#include "units.h"
#include "jsonparser.h"

Unit::Unit(std::string name, int hp, int damage) :m_name(name), m_hp(hp), m_damage(damage) {}

void Unit::dealDamageTo(Unit& damagedUnit){
	damagedUnit.m_hp = damagedUnit.getHp() - this->getDamage() < 0 ? 0 : damagedUnit.getHp() - this->getDamage();
}

Unit* Unit::parseUnit(const std::string& filename){
	//Istream
	std::ifstream input;
	input.open(filename);
	if (input.fail())
	{
		throw 1;
	}
	std::map<std::string, std::string> values = JsonParser::ParseIstream(input);
	input.close();
	//File
	//std::map<std::string,std::string> values=JsonParser::ParseFile(filename);
	Unit* unit=new Unit(values["name"],std::stoi(values["hp"]), std::stoi(values["dmg"]));
	return unit;
}
