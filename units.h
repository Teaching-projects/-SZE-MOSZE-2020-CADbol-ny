#pragma once
#include <string>
/**
* \class Unit
*
*
*
*	This is the class that represents the units in the game.
*	The units have name,healt points,attack damage, attackcooldown.
*
*/
class Unit {
protected:
	const std::string m_name; ///<This is the unit's name.
	int m_hp;///<This is the unit's default healt points.
	int m_damage;///<This is the unit's default damage.
	float m_attackCooldown;///<This is the unit's attackcooldown.
public:
	/// This is the constructor for the units.
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
	int getHealthPoints() const { return m_hp; }
	/// This is a simple setter for the unit's healt.
	void setHp(int newHp) { m_hp=newHp; }
	/// Getter for the units damage.
	/// 
	/// This is a simple getter function.
	/// <returns>The unit's current damage.
	int getDamage() const { return m_damage; }
	/// Getter for the units attackspeed.
	/// 
	/// This is a simple getter function.
	/// <returns>The unit's current attackspeed cooldown
	float getAttackCoolDown() const { return m_attackCooldown; }
	/// This is a boolean function to check units healt points.
	///
	/// This function returns true or false according to the units healt. 
	/// <returns> True: If the unit is alive.
	/// <returns> False: If the unit is dead.
	bool isAlive() const { return m_hp>0; }
	/// This is the function for reading the units from a file.
	/// 
	/// @param fileName This is the file which contains the unit attributes in .json format.
	/// <returns> It returns a unit.
	static Unit parse(const std::string&);
	///This is the destructor
	/// 
	/// 
	~Unit() {}
};

