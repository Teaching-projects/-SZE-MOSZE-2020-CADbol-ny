#include "Main.h"

//constructors
Unit::Unit(){
	std::string name;
	int hp, damage;
	std::cin >> name >> hp >> damage;
	Unit::setName(name);
	Unit::setHp(hp);
	Unit::setDamage(damage);
}
Unit::Unit(std::string name, int hp, int damage):m_name(name),m_hp(hp),m_damage(damage) {}
//unit's death
bool Fight::endGame(Unit& unit1,Unit& unit2){
	return unit1.getHp() == 0 || unit2.getHp() == 0 ? false : true;
}
//Gameplay
void Fight::startGame(Unit& unit1, Unit& unit2){
	unit1.listAllAttributes();
	unit2.listAllAttributes();
	while (Fight::endGame(unit1, unit2))
	{
		if (Fight::endGame(unit1, unit2))
		{
			unitAttack(unit1, unit2);
			std::cout << unit1.getName() << "->" << unit2.getName() << std::endl;
			unit1.listAllAttributes();
			unit2.listAllAttributes();
		}
		if (Fight::endGame(unit1, unit2))
		{
			unitAttack(unit2, unit1);
			std::cout << unit2.getName() << "->" << unit1.getName() << std::endl;
			unit1.listAllAttributes();
			unit2.listAllAttributes();
		}
	}
	if (unit1.getHp() == 0)
	{
		std::cout << unit1.getName() << " died." << unit2.getName() << " wins." << std::endl;
	}
	else if(unit2.getHp() == 0)
	{
		std::cout << unit2.getName() << " died." << unit1.getName() << " wins." << std::endl;
	}
}

int main()
{
	Unit unit1,unit2;
	Fight::startGame(unit1,unit2);
	std::cin.get();
}