#include "Monster.h" 
#include <fstream>
#include <cmath>
#include "JSON.h"
#include <exception>

void Monster::dealPhysicalDamageTo(Hero& damagedUnit)
{
		int aktdamage = getFDamage()-damagedUnit.getDefense() >=0 ? getFDamage()-damagedUnit.getDefense() : 0;
		int damageDone = aktdamage > damagedUnit.getHealthPoints() ? damagedUnit.getHealthPoints(): aktdamage;
		damagedUnit.setHp(damagedUnit.getHealthPoints() - damageDone);
}

void Monster::dealMagicalDamageTo(Hero& damagedUnit)
{
		int damageDone = getMDamage() > damagedUnit.getHealthPoints() ? damagedUnit.getHealthPoints(): getMDamage();
		damagedUnit.setHp(damagedUnit.getHealthPoints() - damageDone);
}

Monster Monster::parse(const std::string& unitfilename){
	//Istream
	std::ifstream inputunit;
	inputunit.open(unitfilename);
	if (inputunit.fail())
	{
		throw JSON::ParseException("Couldn't open file,the file doesn't exist.");
	}
	JSON values = JSON::parseFromIstream(inputunit);
	inputunit.close();
	//File
	//std::map<std::string,std::string> values=JsonParser::ParseFile(unitfilename);
	return Monster(values.get<std::string>("name"),values.get<int>("health_points"), values.get<int>("physical_damage"),values.get<int>("magical_damage"),values.get<float>("attack_cooldown"),values.get<int>("defense"),values.get<std::string>("texture"),values.get<std::string>("lore"));
}