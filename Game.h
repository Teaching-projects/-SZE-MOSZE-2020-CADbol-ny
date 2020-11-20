#pragma once

#include <string>
#include <list>

#include "Map.h"
#include "Monster.h"
#include "Hero.h"
#include "JSON.h"

class Game:public Map{
	Map gamemap;
public:
	Game(std::string);

	void setMap(Map);

	void putHero(Hero hero, int, int);

	void putMonster(Monster monster, int, int);

	bool heroIsPresent();

	static void run();

	class OccupiedException: std::logic_error{
		public: OccupiedException(const char * what): std::logic_error(what){}
	};

	class AlreadyHasHeroException: std::logic_error{
		public: AlreadyHasHeroException(const char * what): std::logic_error(what){}
	};

	class AlreadyHasUnitException: std::logic_error{
		public: AlreadyHasUnitException(const char * what): std::logic_error(what){}
	};

	class NotInitializedException: std::logic_error{
		public: NotInitializedException(const char * what): std::logic_error(what){}
	};
};