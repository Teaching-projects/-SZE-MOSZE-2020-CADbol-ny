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
struct position {
		int x=-1,y=-1;
	};
struct Damage{
	int physical=0;
    int magical=0;

	inline Damage& operator +(Damage const& obj){
		this->physical=obj.physical;
		this->magical=obj.magical;
		return *this;
	}
	inline Damage& operator +=(Damage const& obj){
		this->physical+=obj.physical;
		this->magical+=obj.magical;
		return *this;
	}
	inline Damage& operator *=(Damage const& obj){
		this->physical*=obj.physical;
		this->magical*=obj.magical;
		return *this;
	}
};
class Unit:public position {
protected:
	const std::string m_name; ///<This is the unit's name.
	int m_hp;///<This is the unit's default healt points.
	Damage damage;///<This is the unit's default damage.
	float m_attackCooldown;///<This is the unit's attackcooldown.
	int m_defense;///<This is the unit's defense.
	position pos;///<This is the unit's position.
	
public:
	
	/// This is the constructor for the units.
	Unit(const std::string& name, int hp, int fdamage,int mdamage, float attackCooldown,int defense);
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
	int getFDamage() const { return damage.physical; }

	int getMDamage() const { return damage.magical; }
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
	void setUnitPosition(int newx,int newy) { pos.x=newx;pos.y=newy;}

	int getUnitPositionX()const { return pos.x;} 

	int getUnitPositionY()const { return pos.y;} 

	inline bool operator==(const Unit& unit) const { 
		return getName()==unit.getName() && getHealthPoints()==unit.getHealthPoints()  && getFDamage()==unit.getFDamage() && getMDamage()==unit.getMDamage() && getAttackCoolDown()==unit.getAttackCoolDown() &&
		getUnitPositionX()==unit.getUnitPositionX() && getUnitPositionY()==unit.getUnitPositionY() ; 
		}
	int getDefense() const { return m_defense; }

	~Unit() {}

};

