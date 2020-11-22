#pragma once

#include <string>
#include <list>

#include "Map.h"
#include "Monster.h"
#include "Hero.h"
#include "JSON.h"

class Game:public Map{
	Map gamemap;
	std::string hero_file="";
	std::list<std::string> monster_files = {};
	int monstercount=0;
public:
	Game(std::string);

	void setMap(Map);

	void putHero(Hero& hero, int, int);

	void putMonster(Monster& monster, int, int);

	bool heroIsPresent();

	void run();

	void init(const std::string&);

	void gameLogAndFight(Hero&, std::list<Monster>&,int,int);

	class OccupiedException:public std::logic_error{
		public: OccupiedException(const char * what): std::logic_error(what){}
	};

	class AlreadyHasHeroException:public std::logic_error{
		public: AlreadyHasHeroException(const char * what): std::logic_error(what){}
	};

	class AlreadyHasUnitException:public std::logic_error{
		public: AlreadyHasUnitException(const char * what): std::logic_error(what){}
	};

	class NotInitializedException:public std::logic_error{
		public: NotInitializedException(const char * what): std::logic_error(what){}
	};
};