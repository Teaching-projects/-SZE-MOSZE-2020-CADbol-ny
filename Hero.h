#include "units.h"

class Hero : public Unit {
 public:
	Hero(const std::string& name, int hp, int damage, float attackCooldown) : Unit( name, hp, damage, attackCooldown){}
 	static Hero parse(const std::string&);
};