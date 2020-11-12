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
    Monster(const std::string& name, int hp, int damage, float attackCooldown,std::string lore) : Unit( name, hp, damage, attackCooldown),lore(lore){}
    /// This is the parse function for the Monster class.
    static Monster parse(const std::string&);
    /// This is the function to attack back at the Hero class.
    void dealDamageTo(Hero&);
};
