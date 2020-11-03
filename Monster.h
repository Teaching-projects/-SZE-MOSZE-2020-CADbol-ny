#include "units.h"

class Monster : public Unit {
public:
    Monster(const std::string& name, int hp, int damage, float attackCooldown) : Unit( name, hp, damage, attackCooldown){}
    static Monster parse(const std::string&);

};