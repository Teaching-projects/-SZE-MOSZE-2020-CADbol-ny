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
	int m_damagebonusperlevel; ///<This is the Hero's damage bonus per level.
	float m_cdmultiplier; ///<This is the Hero's attack cooldown multiplier.
	int m_xp; ///<This is the Hero's experience points.
	int m_maxhp; ///<This is the Hero's maximum healt points.
	int m_level; ///<This is the Hero's level.
 public:
 	///This is the constructor for the Hero class.
	Hero(const std::string& name, int hp, int damage, float attackCooldown,int xplevel,int hpbonuslevel,int damagebonus,float multiplier) : 
	Unit( name, hp, damage, attackCooldown),m_xplevel(xplevel),m_hpbonuslevel(hpbonuslevel),m_damagebonusperlevel(damagebonus),m_cdmultiplier(multiplier),m_xp(0),m_maxhp(hp),m_level(1)
	{}
	/// This is the parse function for the Hero class.
 	static Hero parse(const std::string&);
	/// Getter for the Hero maximum healt points.
	/// 
	/// This is a simple getter function.
	/// <returns>The Hero's current max hp.
	int getMaxHealthPoints() const { return m_maxhp; }
	/// Getter for the Hero level.
	/// 
	/// This is a simple getter function.
	/// <returns>The Hero's current level.
	int getLevel() const { return m_level;}
	/// Getter for the Hero experience points.
	/// 
	/// This is a simple getter function.
	/// <returns>The Hero's current xp.
	int getXp() const {return m_xp;}
	/// This function is the fight mechanics.
	/// 
	/// 
	/// This function makes the Hero and the Monster attack each other until one of them dies. Also, it
 	/// gives the Hero xp according to its dealt damage, then gives that
 	/// amount in experience point to it. After every 100 xp the Hero levels up. 
 	/// Which means it stats gets stronger by the multiplier bonuses.
	void fightTilDeath(Monster&);
	/// This is the function to deal damage to the Monster class.
	void dealDamageTo(Monster&);
};
