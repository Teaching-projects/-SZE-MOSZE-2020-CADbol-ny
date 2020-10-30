#pragma once
#include <string>
/**
* \class Unit
*
*
*
*	This is the class that represents the units in the game.
*	The units have name,healt points,attack damage and attackcooldown.
*	They can attack each other back and forth, until one of them dies.
*
*/
class Unit {
private:

	const std::string m_name; ///<This is the unit's name.
	int m_hp;///<This is the unit's default healt points.
	int m_damage;///<This is the unit's default damage.
	float m_attackCooldown;///<This is the unit's attackcooldown.
  	int m_xp;///<This is the unit's current experience
	int m_level;///<This is the unit's level
	int m_maxHP;///<This is the unit's HP after levelups
public:
	/// This is the constructor for the units.
	///
	///We get the constructor parameters from the file, which is in .json format.
	Unit(const std::string& name, int hp, int damage, float attackCooldown);
	///	Getter for the units name.
	/// 
	/// This is a simple getter function.
	/// <returns>The unit's name
	const std::string &getName() const { return m_name; }
	/// Getter for the units healt points.
	/// 
	/// This is a simple getter function.
	/// <returns>The unit's current hp.
	int getHp() const { return m_hp; }
	/// Getter for the units damage.
	/// 
	/// This is a simple getter function.
	/// <returns>The unit's current damage.
	int getDamage() const { return m_damage; }
	/// Getter for the units attackspeed.
	/// 
	/// This is a simple getter function.
	/// <returns>The unit's current damage.
	float getAttackspeed() const { return m_attackCooldown; }
	/// This is the function for dealing damage.
	/// 
	/// Units can use this function to lower the other unit healt points.
	/// <param name="unit1" This tells the function who gets "hurt".
	void dealDamageTo(Unit&);
	/// This makes the units hit each other.
	/// 
	/// This fight function takes two unit pointers. Unit1 attacks the unit2 first, then according to the attackspeed parameters, units
	/// hit each other until one of them dies.
	/// <param name="unit1" This is the unit which attacks first, and the so called "agressor".
	/// <param name="unit2" This is the unit which "defends".
	static void Fight(Unit*, Unit*);
	/// This is the function for reading the units from a file.
	/// 
	/// @param fileName This is the file which contains the unit attributes in .json format.
	/// <returns> It returns a unit.
	static Unit* parseUnit(const std::string&);
	///This is the destructor
	/// 
	/// 
	~Unit() {}
};

