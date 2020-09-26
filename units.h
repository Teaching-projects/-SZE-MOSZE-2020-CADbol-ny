#pragma once
#include <string>
class Unit {
private:
	mutable std::string m_name;
	int m_hp;
	mutable int m_damage;
public:
	Unit() {};
	Unit(std::string, int, int);
	std::string getName() const { return m_name; }
	int getHp() const { return m_hp; }
	int getDamage() const { return m_damage; }
	void dealDamageTo(Unit&);
	static void parseUnit(std::string, Unit&);
	~Unit() {}
};
