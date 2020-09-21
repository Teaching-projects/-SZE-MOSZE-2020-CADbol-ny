#include "units.h"

Unit::Unit(std::string name, int hp, int damage) :m_name(name), m_hp(hp), m_damage(damage) {}

void Unit::dealDamageTo(Unit& damagedUnit){
	damagedUnit.m_hp = damagedUnit.getHp() - this->getDamage() < 0 ? 0 : damagedUnit.getHp() - this->getDamage();
}