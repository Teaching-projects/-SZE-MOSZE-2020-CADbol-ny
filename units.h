#pragma once
#include <string>

class Unit {
private:
	const std::string m_name;
	int m_hp;
	int m_damage;
	int m_xp;
	int m_level;
	int m_maxHP;

public:
	Unit(const std::string&, int, int);
	std::string getName() const { return m_name; }
	int getHp() const { return m_hp; }
	int getDamage() const { return m_damage; }
	void dealDamageTo(Unit&);
	static Unit* parseUnit(const std::string&);
	~Unit() {}
};

