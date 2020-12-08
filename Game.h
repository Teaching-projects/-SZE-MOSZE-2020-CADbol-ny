#pragma once

#include <string>
#include <list>

#include "Map.h"
#include "Monster.h"
#include "Hero.h"
#include "JSON.h"
#include "Renderer.h"

class Renderer;
/**
 * \class Game
 * 
 * \brief This is the class for the Gameplay.
 * 
 * 
 * This class is derived from the Map class. 
 * 
 * 
*/
class Game: public Map{
protected:
	Map gamemap;///<This is the Gamemap.
	Hero hero;///<This is the Hero on the map.
	std::list<Monster> monsters={};///<These are the Monsters on the map.
	int monstercount=0;///<This is the number of monsters on the map.
	std::list<Renderer*> renderers={};///<These are the assigned renderers.
	JSON scenario;///<This is the JSON object for storing the file content.
	///This function prints the current fight result.
	void gameLogAndFight(Hero&, std::list<Monster>&,int,int);

public:
	///This is a simple getter function which returns the walltexture.
	std::string getWallTexture(){return scenario.get<std::string>("wall_texture");}
	///This is a simple getter function which returns the freetexture.
	std::string getFreeTexture(){return scenario.get<std::string>("free_texture");}
	///This is a simple getter function which returns the herotexture.
	std::string GetHeroTexture()const{return hero.getTexture();}
	///This is a simple getter function which returns the monstertexture.
	std::string getMonsterTexture(char x){
		std::string monster="monster-";
		monster+=x;
		Monster mon(Monster::parse(scenario.get<std::string>(monster)));
		return mon.getTexture();
	}
	///This function registers renderers.
    void registerRenderer(Renderer* rend){
		renderers.push_back(rend);
	}
	///Function for checking the hero's presence on the map.
	/// 
	/// 
	/// <returns>True if the hero is present and false if it is not.
	bool heroIsPresent();
	///This is the default constructor for the Game class.
	Game(){}
	///This is the constructor for the Game class.
	explicit Game(const std::string&);
	///This is a simple setter function which sets the map.
	void setMap(const Map&);
	///This is the function for putting the hero on the map.
	void putHero(Hero& hero, int, int);
	///This is the function for putting the monsters on the map.
	void putMonster(Monster& monster, int, int);
	/// Getter for the map size.
	/// 
	/// This is a simple getter function.
	/// <returns>The map size.
	int getGameMapSize() const { return gamemap.getMapSize();}
	/// Getter for the current row size.
	/// 
	/// This is a simple getter function.
	/// <returns>The row size.
	int getGameMapRowSize(int x) const { return gamemap.getRowSize(x);}
	/// Getter for the map.
	/// 
	/// This is a simple getter function.
	/// <returns>The map.
	Map& getMap() const { return const_cast<Map&>(gamemap);}
	/// Getter for the Hero.
	/// 
	/// This is a simple getter function.
	/// <returns>The Hero.
	Hero& getHero() const { return const_cast<Hero&>(hero);}
	/// Getter for the Monsters.
	/// 
	/// This is a simple getter function.
	/// <returns>The Monsters.
	std::list<Monster>& getMonster() const { return const_cast<std::list<Monster>&>(monsters);}	
	///This function is the gameloop.
	virtual void run();
	/**
	 * \class OccupiedException
	 * 
	 * \brief This class is for the errors.
	 * 
	 * 
	 * This class handles the field errors.
	*/
	class OccupiedException:public std::logic_error{
		public: 
		///This is the constructor for the class.
		explicit OccupiedException(const char * what): std::logic_error(what){}
	};
	/**
	 * \class AlreadyHasHeroException
	 * 
	 * \brief This class is for the errors.
	 * 
	 * 
	 * This class handles the hero putting errors.
	*/
	class AlreadyHasHeroException:public std::logic_error{
		public: 
		///This is the constructor for the class.
		explicit AlreadyHasHeroException(const char * what): std::logic_error(what){}
	};
	/**
	 * \class AlreadyHasUnitException
	 * 
	 * \brief This class is for the errors.
	 * 
	 * 
	 * This class handles the unit putting errors.
	*/
	class AlreadyHasUnitsException:public std::logic_error{
		public: 
		///This is the constructor for the class.
		explicit AlreadyHasUnitsException(const char * what): std::logic_error(what){}
	};
	/**
	 * \class NotInitializedException 
	 * 
	 * \brief This class is for the errors.
	 * 
	 * 
	 * This class handles the map errors.
	*/
	class NotInitializedException:public std::logic_error{
		public: 
		///This is the constructor for the class.
		explicit NotInitializedException(const char * what): std::logic_error(what){}
	};

};