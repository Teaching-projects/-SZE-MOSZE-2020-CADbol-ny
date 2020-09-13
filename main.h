#pragma once
#include<iostream>
#include<string>
//classes and function declarations
class Unit {
private:
	std::string m_name;
	int m_hp;
	int m_damage;
public:
	Unit();
	Unit(std::string, int, int);
	std::string getName() const { return m_name; }
	int getHp() const { return m_hp; }
	int getDamage() const { return m_damage; }
	std::string setName(std::string m_name) { return this->m_name = m_name; }
	int setHp(int m_hp) { return this->m_hp = m_hp; }
	int setDamage(int m_damage) { return this->m_damage = m_damage; }
	void listAllAttributes()const 
	{
		std::cout << this->m_name << ":HP:" << this->m_hp << ",DMG:" << this->m_damage << std::endl;
	}
	~Unit() {}
};

class Fight {
public:
	static void unitAttack(Unit& aggressorUnit,Unit& damagedUnit)
	{
		damagedUnit.setHp(damagedUnit.getHp()-aggressorUnit.getDamage() < 0 ? 0:damagedUnit.getHp()-aggressorUnit.getDamage());
	}
	static bool endGame(Unit&, Unit&);
	static void startGame(Unit&, Unit&);
};