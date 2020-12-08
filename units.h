#pragma once
#include <string>

/**
* \struct position
*
*
*
*	This is the struct that represents the unit's position on the map.
*	It has x and y coordinates.
*
*/
struct position {
		int x=-1,y=-1;///<X and Y coordinates.
	};
/**
* \struct Damage
*
*
*
*	This is the struct that represents the unit's damage.
*	It can be physical or magical.
*
*/
struct Damage{
	int physical=0;///<Physical damage.
    int magical=0;///<Magical damage.
	/// This is the overloaded + operator.
	inline Damage& operator +(Damage const& obj){
		this->physical=obj.physical;
		this->magical=obj.magical;
		return *this;
	}
	/// This is the overloaded += operator.
	inline Damage& operator +=(Damage const& obj){
		this->physical+=obj.physical;
		this->magical+=obj.magical;
		return *this;
	}
	/// This is the overloaded *= operator.
	inline Damage& operator *=(Damage const& obj){
		this->physical*=obj.physical;
		this->magical*=obj.magical;
		return *this;
	}
};
/**
* \class Unit
*
*
*
*	This is the class that represents the units in the game.
*	The units have name,healt points,attack damage(magical,physical), attackcooldown,defense and position.
*
*/
class Unit:public position {
protected:
	std::string m_name; ///<This is the unit's name.
	int m_hp;///<This is the unit's default healt points.
	Damage damage;///<This is the unit's default damage(physical,magical).
	float m_attackCooldown;///<This is the unit's attackcooldown.
	int m_defense;///<This is the unit's defense.
	position pos;///<This is the unit's position.
	std::string m_texture;///<This is the unit's texture.
	
public:
	/// This is the default constructor for the units.
	Unit(){}
	/// This is the constructor for the units.
	explicit Unit(const std::string& name, int hp, int fdamage,int mdamage, float attackCooldown,int defense,const std::string& texture);
	///	Getter for the unit's name.
	/// 
	/// This is a simple getter function.
	/// <returns>The unit's name
	std::string getName() const { return m_name; }
	/// Getter for the unit's healt points.
	/// 
	/// This is a simple getter function.
	/// <returns>The unit's current hp.
	int getHealthPoints() const { return m_hp; }
	/// This is a simple setter for the unit's healt.
	void setHp(int newHp) { m_hp=newHp; }
	/// Getter for the unit's physical damage.
	/// 
	/// This is a simple getter function.
	/// <returns>The unit's current physical damage.
	int getFDamage() const { return damage.physical; }
	/// Getter for the unit's texture.
	/// 
	/// This is a simple getter function.
	/// <returns>The unit's texture.
	std::string getTexture() const { return m_texture;}
	/// Getter for the unit's magical damage.
	/// 
	/// This is a simple getter function.
	/// <returns>The unit's current magical damage.
	int getMDamage() const { return damage.magical; }
	/// Getter for the unit's attackspeed.
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
	/// This is a simple setter for the unit's positon.
	void setUnitPosition(int newx,int newy) { pos.x=newx;pos.y=newy;}
	/// Getter for the unit's position coordinate x.
	/// 
	/// This is a simple getter function.
	/// <returns>The unit's current position coordinate x.
	int getUnitPositionX()const { return pos.x;} 
	/// Getter for the unit's position coordinate y.
	/// 
	/// This is a simple getter function.
	/// <returns>The unit's current position coordinate y.
	int getUnitPositionY()const { return pos.y;} 
	/// This is the overloaded == operator.
	inline bool operator==(const Unit& unit) const { 
		return getName()==unit.getName() && getHealthPoints()==unit.getHealthPoints()  && getFDamage()==unit.getFDamage() && getMDamage()==unit.getMDamage() && getAttackCoolDown()==unit.getAttackCoolDown() &&
		getUnitPositionX()==unit.getUnitPositionX() && getUnitPositionY()==unit.getUnitPositionY() ; 
	}
	/// Getter for the unit's defense.
	/// 
	/// This is a simple getter function.
	/// <returns>The unit's current defense
	int getDefense() const { return m_defense; }
	/// This is the overloaded = operator.
	inline Unit& operator=(const Unit& unit){
		this->m_name=unit.m_name;
		this->m_hp=unit.m_hp;
		this->damage.magical=unit.damage.magical;
		this->damage.physical=unit.damage.physical;
		this->m_attackCooldown=unit.m_attackCooldown;
		this->m_defense=unit.m_defense;
		this->m_texture=unit.m_texture;
		return *this;
	}
	///This is the destructor
	/// 
	/// 
	~Unit() {}

};

