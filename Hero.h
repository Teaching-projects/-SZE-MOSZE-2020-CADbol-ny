#pragma once
#include "units.h"
#include "Monster.h"

class Monster;

class Hero : public Unit {
 private:
	int m_xplevel;
	int m_hpbonuslevel;
	int m_damagebonusperlevel;
	float m_cdmultiplier;
	int m_xp;
	int m_maxhp;
	int m_level;
 public:
	Hero(const std::string& name, int hp, int damage, float attackCooldown,int xplevel,int hpbonuslevel,int damagebonus,float multiplier) : 
	Unit( name, hp, damage, attackCooldown),m_xplevel(xplevel),m_hpbonuslevel(hpbonuslevel),m_damagebonusperlevel(damagebonus),m_cdmultiplier(multiplier),m_xp(0),m_maxhp(hp),m_level(1)
	{}
 	static Hero parse(const std::string&);

	int getMaxHealthPoints() const { return m_maxhp; }

	int getLevel() const { return m_level;}

	int getXp() const {return m_xp;}

	void fightTilDeath(Monster&);

	void dealDamageTo(Monster&);
};
