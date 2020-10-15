#include "units.h"
#include <fstream>
#include <cmath>

Unit::Unit(std::string name, int hp, int damage) :m_name(name), m_hp(hp), m_damage(damage), m_xp(0), m_level(1), m_maxHP(m_hp) {}

void Unit::dealDamageTo(Unit& damagedUnit){
	int damageDone = getDamage() > damagedUnit.getHp() ? damagedUnit.getHp(): getDamage();
	damagedUnit.m_hp = damagedUnit.getHp() - damageDone;
	m_xp += damageDone;

	while(m_xp >= 100){
		 m_level +=1;
		 m_xp -= 100;
		 m_maxHP = std::round(1.1*m_maxHP);
		 m_hp = m_maxHP;
		 m_damage = std::round(1.1*m_damage);
	}
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
