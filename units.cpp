#include "units.h"
#include <fstream>

Unit::Unit(std::string name, int hp, int damage) :m_name(name), m_hp(hp), m_damage(damage) {}

void Unit::dealDamageTo(Unit& damagedUnit){
	damagedUnit.m_hp = damagedUnit.getHp() - this->getDamage() < 0 ? 0 : damagedUnit.getHp() - this->getDamage();
}

Unit* Unit::parseUnit(const std::string& fileName){
	std::ifstream fileStream;
	std::string name;
	int hp, damage;
	fileStream.open(fileName);
	if(fileStream.fail()){
		throw 1;
	}
	std::string lines [5];
	int i = 0;
	while (std::getline(fileStream, lines[i])) {
		i++;
	}
	name = lines[1].substr(lines[1].find(':') + 3, lines[1].find(',') - lines[1].find(':') - 4);
	hp = std::stoi(lines[2].substr(lines[2].find(':') + 2, lines[2].find(',') - lines[1].find(':')));
	damage = std::stoi(lines[3].substr(lines[3].find(':') + 2, lines[3].size() - lines[1].find(':')));
	Unit* unit=new Unit(name, hp, damage);
	fileStream.close();
	return unit;
}
