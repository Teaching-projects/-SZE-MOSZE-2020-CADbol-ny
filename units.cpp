#include "units.h"
#include <fstream>
#include <cmath>
#include "JSON.h"
#include <exception>


Unit::Unit(const std::string& name, int hp, int fdamage,int mdamage, float attackCooldown,int defense,const std::string& texture) :m_name(name), m_hp(hp), m_attackCooldown(attackCooldown),m_defense(defense),m_texture(texture) {
	damage.physical=fdamage;
	damage.magical=mdamage;
}

Unit Unit::parse(const std::string& unitfilename){
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
	return Unit(values.get<std::string>("name"),values.get<int>("hp"), values.get<int>("physical_dmg"), values.get<int>("magical_dmg"),values.get<float>("attackcooldown"),values.get<int>("defense"),values.get<std::string>("texture"));
}
