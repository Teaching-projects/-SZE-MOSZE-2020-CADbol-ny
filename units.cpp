#include "units.h"
#include <fstream>
#include <cmath>
#include "JSON.h"
#include <exception>


Unit::Unit(const std::string& name, int hp, int damage, float attackCooldown) :m_name(name), m_hp(hp), m_damage(damage), m_attackCooldown(attackCooldown), m_xp(0), m_level(1), m_maxHP(m_hp) {}

void Unit::dealDamageTo(Unit& damagedUnit){
	int damageDone = getDamage() > damagedUnit.getHealthPoints() ? damagedUnit.getHealthPoints(): getDamage();
	damagedUnit.m_hp = damagedUnit.getHealthPoints() - damageDone;
	m_xp += damageDone;

	while(m_xp >= 100){
		 m_level +=1;
		 m_xp -= 100;
		 m_maxHP = std::round(1.1*m_maxHP);
		 m_hp = m_maxHP;
		 m_damage = std::round(1.1*m_damage);
		 m_attackCooldown = 0.9*m_attackCooldown;
	}
}

void Unit::Fight(Unit* unit1, Unit* unit2) {
	unit1->dealDamageTo(*unit2);
	float nextattackunit1 = unit1->getAttackCoolDown();
	float nextattackunit2 = unit2->getAttackCoolDown();
	while (unit1->getHealthPoints() != 0 && unit2->getHealthPoints() != 0) {
		if (nextattackunit1 <= nextattackunit2) {
			unit1->dealDamageTo(*unit2);
			nextattackunit1 += unit1->getAttackCoolDown();
		}
		else {
			unit2->dealDamageTo(*unit1);
			nextattackunit2 += unit2->getAttackCoolDown();
		}
	}
}

void Unit::fightTilDeath(Unit enemy) {
	Unit::Fight(this, &enemy);
}

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
