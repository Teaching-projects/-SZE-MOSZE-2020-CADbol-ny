#pragma once

#include <string>

#include "Map.h"
#include "Monster.h"
#include "Hero.h"

class Game:public Map {
	Map gamemap;
public:
	Game(std::string);

	void setMap(Map);

	void putHero(Hero hero, int, int);

	void putMonster(Monster monster, int, int);

	class OccupiedException: std::logic_error
	{
		public: OccupiedException(const char * what): std::logic_error(what){}
	};
};