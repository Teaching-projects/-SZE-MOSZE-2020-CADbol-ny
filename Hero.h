#pragma once
#include "units.h"
#include "Monster.h"

class Monster;
/**
 * \class Hero
 * 
 * \brief This is the class for the Hero unit.
 * 
 * 
 * This class is derived from the Unit class. 
 * 
 * 
*/
class Hero : public Unit {
 private:
	int m_xplevel; ///<This is the Hero's xp level.
	int m_hpbonuslevel; ///<This is the Hero's healt points bonus per level.
	int m_physicaldamagebonusperlevel; ///<This is the Hero's physicaldamage bonus per level.
	int m_magicaldamagebonusperlevel;///<This is the Hero's magicaldamage bonus per level.
	int m_defense_bonus_per_level;///<This is the Hero's defense bonus per level.
	float m_cdmultiplier; ///<This is the Hero's attack cooldown multiplier.
	int m_xp; ///<This is the Hero's experience points.
	int m_maxhp; ///<This is the Hero's maximum healt points.
	int m_level; ///<This is the Hero's level.
	int m_light_radius;///<This is the Hero's vision on the map.
	int m_light_radius_bonus_per_level=1;///<This is the Hero's vision bonus per level.
 public:
 Hero(){}
 	///This is the constructor for the Hero class.
	Hero(std::string name, int hp, int fdamage,int mdamage, float attackCooldown,int defense,int xplevel,int hpbonuslevel,int fdamagebonus,int mdamagebonus,
	int defensebonus,float multiplier,int lightrad,int lightradbonus) : 
	Unit( name, hp, fdamage,mdamage, attackCooldown,defense),m_xplevel(xplevel),m_hpbonuslevel(hpbonuslevel),m_physicaldamagebonusperlevel(fdamagebonus),
	m_magicaldamagebonusperlevel(mdamagebonus),m_defense_bonus_per_level(defensebonus),m_cdmultiplier(multiplier),m_xp(0),m_maxhp(hp),m_level(1),
	m_light_radius(lightrad),m_light_radius_bonus_per_level(lightradbonus)
	{}
	/// This is the parse function for the Hero class.
 	static Hero parse(const std::string&);
	/// Getter for the Hero's maximum healt points.
	/// 
	/// This is a simple getter function.
	/// <returns>The Hero's current max hp.
	int getMaxHealthPoints() const { return m_maxhp; }
	/// Getter for the Hero level.
	/// 
	/// This is a simple getter function.
	/// <returns>The Hero's current level.
	int getLevel() const { return m_level;}
	/// Getter for the Hero's experience points.
	/// 
	/// This is a simple getter function.
	/// <returns>The Hero's current xp.
	int getXp() const {return m_xp;}
	/// Getter for the Hero's light radius.
	/// 
	/// This is a simple getter function.
	/// <returns>The Hero's current light radius.
	int getLightRadius() const { return m_light_radius;}
	/// This function is the fight mechanics.
	/// 
	/// 
	/// This function makes the Hero and the Monster attack each other until one of them dies. Also, it
 	/// gives the Hero xp according to its dealt damage, then gives that
 	/// amount in experience point to it. After every 100 xp the Hero levels up. 
 	/// Which means it stats gets stronger by the multiplier bonuses.
	void fightTilDeath(Monster&);
	/// This is the function for leveling up.
	void levelUp();
	/// This is the function to deal physical damage to a monster.
	void dealPhysicalDamageTo(Monster&);
	/// This is the function to magical deal damage to a monster.
	void dealMagicalDamageTo(Monster&);
	/// This is the overloaded assignment operator.
	inline void operator=(const Hero& hero){
		this->m_attackCooldown=hero.m_attackCooldown;
		this->m_cdmultiplier=hero.m_cdmultiplier;
		this->m_defense=hero.m_defense;
		this->m_defense_bonus_per_level=hero.m_defense_bonus_per_level;
		this->m_name=hero.m_name;
		this->m_hp=hero.m_hp;
		this->m_hpbonuslevel=hero.m_hpbonuslevel;
		this->m_magicaldamagebonusperlevel=hero.m_magicaldamagebonusperlevel;
		this->m_physicaldamagebonusperlevel=hero.m_physicaldamagebonusperlevel;
		this->m_xp=hero.m_xp;
		this->m_xplevel=hero.m_xplevel;
		this->damage.magical=hero.damage.magical;
		this->damage.physical=hero.damage.physical;
		this->m_level=hero.m_level;
		this->m_maxhp=hero.m_maxhp;
		this->pos.x=hero.pos.x;
		this->pos.y=hero.pos.y;
		this->m_light_radius=hero.m_light_radius;
	}
};
