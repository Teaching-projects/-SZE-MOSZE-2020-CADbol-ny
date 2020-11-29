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
    Monster(std::string name, int hp, int fdamage,int mdamage, float attackCooldown,int defense,std::string lore) : Unit( name, hp, fdamage,mdamage, attackCooldown,defense),lore(lore){}
    /// This is the parse function for the Monster class.
    static Monster parse(const std::string&);
    /// This is the function to attack back at the Hero class.
    void dealDamageTo(Hero&);

    inline bool operator==(const Monster& unit) const { 
		return lore==unit.lore && getName()==unit.getName() && getHealthPoints()==unit.getHealthPoints()  && getFDamage()==unit.getFDamage()  && getMDamage()==unit.getMDamage() && getAttackCoolDown()==unit.getAttackCoolDown() &&
		getUnitPositionX()==unit.getUnitPositionX() && getUnitPositionY()==unit.getUnitPositionY() ; 
    }
};
