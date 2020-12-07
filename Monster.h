#pragma once
#include "units.h"
#include "Hero.h"

class Hero;
/**
 * \class Monster
 * 
 * \brief This is the class for the Monsters.
 * 
 * This class is derived from the Unit class.
 * 
*/

class Monster : public Unit {
private:
    std::string lore;///<This is the unit's lore.
public:
    /// This is the constructor for the class.
    Monster(std::string name, int hp, int fdamage,int mdamage, float attackCooldown,int defense,std::string texture,std::string lore) : Unit( name, hp, fdamage,mdamage, attackCooldown,defense,texture),lore(lore){}
    /// This is the parse function for the Monster class.
    static Monster parse(const std::string&);
    /// This is the function to attack back at the Hero class with physical damage.
    void dealPhysicalDamageTo(Hero&);
    /// This is the function to attack back at the Hero class with magical damage.
     void dealMagicalDamageTo(Hero&);
    /// This is the overloaded == operator.
    inline bool operator==(const Monster& unit) const { 
		return lore==unit.lore && getName()==unit.getName() && getHealthPoints()==unit.getHealthPoints()  && getFDamage()==unit.getFDamage()  && getMDamage()==unit.getMDamage() && getAttackCoolDown()==unit.getAttackCoolDown() &&
		getUnitPositionX()==unit.getUnitPositionX() && getUnitPositionY()==unit.getUnitPositionY() && getTexture()==unit.getTexture() ; 
    }
    /// This is the overloaded != operator.
    inline bool operator!=(const Monster& unit){
      return !operator==(unit);
    }
};
