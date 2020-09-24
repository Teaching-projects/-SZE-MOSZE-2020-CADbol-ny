#include "units.h"

Unit::Unit(std::string name, int hp, int damage) :m_name(name), m_hp(hp), m_damage(damage) {}

void Unit::dealDamageTo(Unit& damagedUnit){
	damagedUnit.m_hp = damagedUnit.getHp() - this->getDamage() < 0 ? 0 : damagedUnit.getHp() - this->getDamage();
}

void Unit::parseUnit(std::string fileName,Unit& unit){
	std::ifstream fileStream;
	fileStream.open(fileName);
	if(fileStream.fail()){
		throw 1;
	}
	while(!fileStream.eof()){
		fileStream>>unit.m_name>>unit.m_hp>>unit.m_damage;
	}
	fileStream.close();
}