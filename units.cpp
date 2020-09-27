#include "units.h"

Unit::Unit(std::string name, int hp, int damage) :m_name(name), m_hp(hp), m_damage(damage) {}

void Unit::dealDamageTo(Unit& damagedUnit){
	damagedUnit.m_hp = damagedUnit.getHp() - this->getDamage() < 0 ? 0 : damagedUnit.getHp() - this->getDamage();
}

void Unit::parseUnit(std::string fileName,Unit& unit){
	std::ifstream fileStream;
	fileStream.open(fileName);
	if(fileStream.fail()){
		throw 1;
	}
	std::string line;
	std::vector <std::string> lines;
	while(std::getline(fileStream,line)){
		lines.push_back(line);
	}
	unit.m_name = lines[1].substr(lines[1].find(':')+3, lines[1].find(',') - lines[1].find(':')-4);
	unit.m_hp=std::stoi(lines[2].substr(lines[2].find(':') + 2, lines[2].find(',') - lines[1].find(':')));
	unit.m_damage=std::stoi(lines[3].substr(lines[3].find(':') + 2, lines[3].size() - lines[1].find(':')));
	fileStream.close();
}
