#include "units.h"
#include "jsonparser.h"
#include <exception>

Unit::Unit(std::string name, int hp, int damage, float attackspeed) :m_name(name),  m_hp(hp), m_damage(damage), m_attackspeed(attackspeed) {}

void Unit::dealDamageTo(Unit& damagedUnit){
	damagedUnit.m_hp = damagedUnit.getHp() - this->getDamage() < 0 ? 0 : damagedUnit.getHp() - this->getDamage();
}

void Unit::Fight(Unit* unit1, Unit* unit2) {
	unit1->dealDamageTo(*unit2);
	float nextattackunit1 = unit1->getAttackspeed();
	float nextattackunit2 = unit2->getAttackspeed();
	while (unit1->getHp() != 0 && unit2->getHp() != 0) {
		if (nextattackunit1 <= nextattackunit2) {
			unit1->dealDamageTo(*unit2);
			nextattackunit1 += unit1->getAttackspeed();
		}
		else {
			unit2->dealDamageTo(*unit1);
			nextattackunit2 += unit2->getAttackspeed();
		}
	}
}
Unit* Unit::parseUnit(const std::string& unitfilename){
	//Istream
	std::ifstream inputunit;
	inputunit.open(unitfilename);
	if (inputunit.fail())
	{
		throw std::runtime_error("Couldn't open file,the file doesn't exist.");
	}
	std::map<std::string, std::string> values = JsonParser::ParseIstream(inputunit);
	inputunit.close();
	//File
	//std::map<std::string,std::string> values=JsonParser::ParseFile(unitfilename);
	Unit* unit=new Unit(values["name"],std::stoi(values["hp"]), std::stoi(values["dmg"]),std::stof(values["attackcooldown"]));
	return unit;
}
