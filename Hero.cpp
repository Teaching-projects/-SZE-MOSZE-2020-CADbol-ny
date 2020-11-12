#include "Hero.h" 
#include <fstream>
#include <cmath>
#include "JSON.h"
#include <exception>

void Hero::dealDamageTo(Monster& damagedUnit)
{
	int damageDone = getDamage() > damagedUnit.getHealthPoints() ? damagedUnit.getHealthPoints(): getDamage();
	damagedUnit.setHp(damagedUnit.getHealthPoints() - damageDone);
	m_xp += damageDone;

	while(m_xp >= m_xplevel){
		 m_level++;
		 m_xp -= m_xplevel;
		 m_maxhp += m_hpbonuslevel; ;
		 m_hp = m_maxhp;
		 m_damage +=m_damagebonusperlevel ;
		 m_attackCooldown *=m_cdmultiplier;
	}
}

void Hero::fightTilDeath(Monster& monster) {
	float nextattackunit1 = this->getAttackCoolDown();
	float nextattackunit2 = monster.getAttackCoolDown();
	while (this->getHealthPoints() != 0 && monster.getHealthPoints() != 0) {
		if (nextattackunit1 <= nextattackunit2) {
			this->dealDamageTo(monster);
			nextattackunit1 += this->getAttackCoolDown();
		}
		else {
			monster.dealDamageTo(*this);
			nextattackunit2 += monster.getAttackCoolDown();
		}
	}
}

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
	return Hero(values.get<std::string>("name"),values.get<int>("base_health_points"), values.get<int>("base_damage"),
	values.get<float>("base_attack_cooldown"),values.get<int>("experience_per_level"),values.get<int>("health_point_bonus_per_level"),
	values.get<int>("damage_bonus_per_level"),values.get<float>("cooldown_multiplier_per_level")
	);
}