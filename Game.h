#pragma once

#include <string>
#include <list>

#include "Map.h"
#include "Monster.h"
#include "Hero.h"
#include "JSON.h"
#include "Renderer.h"

class Renderer;

class Game: public Map{
protected:
	Map gamemap;
	Hero hero;
	std::list<Monster> monsters={};
	int monstercount=0;
	std::list<Renderer*> renderers={};

	Game(){}
	
	Game(const std::string&);

	void setMap(Map);

	void putHero(Hero& hero, int, int);

	void putMonster(Monster& monster, int, int);

	bool heroIsPresent();

	void init(const std::string&);

	void gameLogAndFight(Hero&, std::list<Monster>&,int,int);

public:

	int getGameMapSize() const { return gamemap.getMapSize();}

	int getGameMapRowSize(int x) const { return gamemap.getRowSize(x);}
	
	Map& getMap() const { return const_cast<Map&>(gamemap);}

	Hero& getHero() const { return const_cast<Hero&>(hero);}

	std::list<Monster>& getMonster() const { return const_cast<std::list<Monster>&>(monsters);}	

	virtual void run();

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