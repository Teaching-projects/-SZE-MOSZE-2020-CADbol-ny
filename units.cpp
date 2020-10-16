#include "units.h"
#include <fstream>

Unit::Unit(std::string name, int damage, int hp, float attackspeed) :m_name(name), m_damage(damage), m_hp(hp), m_attackspeed(attackspeed) {}

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

Unit* Unit::parseUnit(const std::string& fileName){
	std::ifstream fileStream;
	std::string name;
	int hp, damage;
	float attackspeed;
	fileStream.open(fileName);
	if(fileStream.fail()){
		throw 1;
	}
	std::string lines [6];
	int i = 0;
	while (std::getline(fileStream, lines[i])) {
		i++;
	}
	name = lines[1].substr(lines[1].find(':') + 3, lines[1].find(',') - lines[1].find(':') - 4);
	hp = std::stoi(lines[2].substr(lines[2].find(':') + 2, lines[2].find(',') - lines[1].find(':')));
	damage = std::stoi(lines[3].substr(lines[3].find(':') + 2, lines[3].find(',') - lines[1].find(':')));
	attackspeed = std::stof(lines[3].substr(lines[4].find(':') + 2, lines[3].size() - lines[1].find(':')));
	Unit* unit=new Unit(name, hp, damage, attackspeed);
	fileStream.close();
	return unit;
}
