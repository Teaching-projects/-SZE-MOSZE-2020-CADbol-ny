#include "Hero.h" 
#include <fstream>
#include <cmath>
#include "JSON.h"
#include <exception>

void Hero::dealDamageTo(Monster& damagedUnit)
{
	int aktdamage= getFDamage()-damagedUnit.getDefense() >=0 ? getFDamage()-damagedUnit.getDefense() : 0;
	int damageDone = aktdamage > damagedUnit.getHealthPoints() ? damagedUnit.getHealthPoints(): aktdamage;
	damagedUnit.setHp(damagedUnit.getHealthPoints() - damageDone);
	m_xp += damageDone;

	while(m_xp >= m_xplevel){
		 m_level++;
		 m_xp -= m_xplevel;
		 m_maxhp += m_hpbonuslevel; ;
		 m_hp = m_maxhp;
		 damage.physical +=m_physicaldamagebonusperlevel ;
		 damage.magical +=m_magicaldamagebonusperlevel ;
		 m_defense+=m_defense_bonus_per_level;
		 m_light_radius+=m_ligt_radius_bonus_per_level;
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
	return Hero(values.get<std::string>("name"),values.get<int>("base_health_points"), values.get<int>("base_physical_damage"),values.get<int>("base_magical_damage"),
	values.get<float>("base_attack_cooldown"),values.get<int>("base_defense"),values.get<int>("experience_per_level"),values.get<int>("health_point_bonus_per_level"),
	values.get<int>("physical_damage_bonus_per_level"),values.get<int>("magical_damage_bonus_per_level"),values.get<int>("defense_bonus_per_level"),
	values.get<float>("cooldown_multiplier_per_level"),values.get<int>("light_radius"),values.get<int>("light_radius_bonus_per_level")
	);
}