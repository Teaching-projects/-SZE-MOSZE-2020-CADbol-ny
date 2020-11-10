#pragma once
#include "units.h"
#include "Hero.h"

class Hero;

class Monster : public Unit {
private:
    std::string lore;
public:
    Monster(const std::string& name, int hp, int damage, float attackCooldown,std::string lore) : Unit( name, hp, damage, attackCooldown),lore(lore){}
    
    static Monster parse(const std::string&);

    void dealDamageTo(Hero&);
};
