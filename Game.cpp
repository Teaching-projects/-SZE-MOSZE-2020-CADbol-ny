#include "Game.h"
#include <iostream>
#include <algorithm>

Game::Game(const std::string& filename) : gamemap(filename) {}

void Game::setMap(const Map& defmap){
	for(int i=0;i<defmap.getMapSize();i++){
		for(int j=0;j<defmap.getRowSize(i);j++){
			if(gamemap.getMapField(i,j)=='H' || gamemap.getMapField(i,j)=='m'){
				throw AlreadyHasUnitsException("The map already has units, can't change it.");
			}		
		}
	}
	gamemap=defmap;
}

void Game::putHero(Hero& Hero, int x, int y) {
	for(int i=0;i<gamemap.getMapSize();i++){
		for(int j=0;j<gamemap.getRowSize(i);j++){
			if(gamemap.getMapField(i,j)=='H'){
				throw AlreadyHasHeroException("There is already a hero on the map, can't place another one.");
			}
		}
	}
	if(gamemap.get(x,y)==Wall){
		throw OccupiedException("The given field is not free.");
	}
	else
	{
		gamemap.setMapField('H',x,y);
		Hero.setUnitPosition(x,y);
		hero=Hero;
	}
	
}

void Game::putMonster(Monster& monster, int x, int y) {
	if(gamemap.get(x,y)==Wall)
	{
		throw OccupiedException("The given field is not free.");
	}
	else
	{
		gamemap.setMapField('m',x,y);
		monster.setUnitPosition(x,y);
		monsters.push_back(monster);
		monstercount++;
	}
}

bool Game::heroIsPresent() {
	bool present=false;
	if(hero.getUnitPositionY()!=-1 && hero.getUnitPositionX()!=-1){
				present=true;
	}
	return present;
}

void Game::gameLogAndFight(Hero& hero, std::list<Monster>& monsters,int x,int y) {
	if(monsters.size()>1){
		for(auto monster: monsters)
		{
			if(monster.getUnitPositionX()==x && monster.getUnitPositionY()==y){
				std::cout 
					<< hero.getName() << "(" << hero.getLevel()<<")"
					<< " vs "
					<< monster.getName()
					<<std::endl;
				hero.fightTilDeath(monster);
				monsters.remove(monster);
				monstercount--;
			}
		}
	}
	else{
		std::cout 
		<< hero.getName() << "(" << hero.getLevel()<<")"
		<< " vs "
		<< monsters.front().getName()
		<<std::endl;
		hero.fightTilDeath(monsters.front());
		monstercount--;
	}
}

void Game::run(){
	if(gamemap.mapIsEmpty() || !Game::heroIsPresent()){
		throw NotInitializedException("The map is not initialized or there is no hero on it.");
	}
	else {
		if(std::any_of(monsters.begin(),monsters.end(),[&](Monster& monster){ return monster.getUnitPositionX()==hero.getUnitPositionX() &&
		monster.getUnitPositionY()==hero.getUnitPositionY();})){
		gameLogAndFight(hero, monsters, hero.getUnitPositionX(), hero.getUnitPositionY());
			if(hero.isAlive()){
				std::cout << "The hero won the fights on that field." << std::endl;
				gamemap.setMapField('H', hero.getUnitPositionX(), hero.getUnitPositionY());
			}
			else{
				std::cout << "The hero died during the fight(s) on that field." << std::endl;
				exit(0);
			}
		}
		while (hero.isAlive() && monstercount!=0) {
			std::string input = "";
			for(auto render:renderers){
				render->render(*this);
			}
			std::cout << "Set input direction:";
			std::cin >> input;
			std::cout<<std::endl;
			if (input == "north") {
				if (hero.getUnitPositionX() - 1 < 0) {
					std::cout << "Map border hit." << std::endl; ;
				}
				else {
					if (gamemap.getMapField(hero.getUnitPositionX() - 1, hero.getUnitPositionY()) != '#')
					{
						if (gamemap.getMapField(hero.getUnitPositionX() - 1, hero.getUnitPositionY()) == ' '){
							gamemap.setMapField('H', hero.getUnitPositionX() - 1, hero.getUnitPositionY());
							gamemap.setMapField(' ', hero.getUnitPositionX(), hero.getUnitPositionY());
							hero.setUnitPosition(hero.getUnitPositionX() - 1,hero.getUnitPositionY());
						}
						else{
							gameLogAndFight(hero, monsters, hero.getUnitPositionX()-1, hero.getUnitPositionY());
							if(hero.isAlive()){
								std::cout << "The hero won the fights on that field." << std::endl;
								gamemap.setMapField('H', hero.getUnitPositionX()-1, hero.getUnitPositionY());
								gamemap.setMapField(' ', hero.getUnitPositionX(), hero.getUnitPositionY());
								hero.setUnitPosition(hero.getUnitPositionX() - 1,hero.getUnitPositionY());
							}
							else{
								std::cout << "The hero died during the fight(s) on that field." << std::endl;
							}
						}
					}
					else
					{
						std::cout << "Wrong input.\n";
					}
				}
			}
			else if (input == "south") {
				if (hero.getUnitPositionX() + 1 >= gamemap.getMapSize()) {
					std::cout << "Map border hit." << std::endl; ;
				}
				else {
					if (gamemap.getMapField(hero.getUnitPositionX() + 1, hero.getUnitPositionY()) != '#')
					{
						if (gamemap.getMapField(hero.getUnitPositionX() + 1, hero.getUnitPositionY()) == ' '){
							gamemap.setMapField('H', hero.getUnitPositionX() + 1, hero.getUnitPositionY());
							gamemap.setMapField(' ', hero.getUnitPositionX(), hero.getUnitPositionY());
							hero.setUnitPosition(hero.getUnitPositionX() + 1,hero.getUnitPositionY());
						}
						else{
							gameLogAndFight(hero, monsters, hero.getUnitPositionX()+1, hero.getUnitPositionY());
							if(hero.isAlive()){
								std::cout << "The hero won the fights on that field." << std::endl;
								gamemap.setMapField('H', hero.getUnitPositionX()+1, hero.getUnitPositionY());
								gamemap.setMapField(' ', hero.getUnitPositionX(), hero.getUnitPositionY());
								hero.setUnitPosition(hero.getUnitPositionX() + 1,hero.getUnitPositionY());
							}
							else{
								std::cout << "The hero died during the fight(s) on that field." << std::endl;
							}
						}
					}
					else
					{
						std::cout << "Wrong input.\n";
					}
				}
			}
			else if (input == "west") {
				if (hero.getUnitPositionY() - 1 < 0) {
					std::cout << "Map border hit." << std::endl; ;
				}
				else {
					if (gamemap.getMapField(hero.getUnitPositionX(), hero.getUnitPositionY() - 1) != '#')
					{
						if (gamemap.getMapField(hero.getUnitPositionX(), hero.getUnitPositionY() - 1) == ' '){
						gamemap.setMapField('H', hero.getUnitPositionX(), hero.getUnitPositionY() - 1);
						gamemap.setMapField(' ', hero.getUnitPositionX(), hero.getUnitPositionY());
						hero.setUnitPosition(hero.getUnitPositionX(),hero.getUnitPositionY()-1);
						}
						else{
							gameLogAndFight(hero, monsters, hero.getUnitPositionX(), hero.getUnitPositionY() - 1);
							if(hero.isAlive()){
								std::cout << "The hero won the fights on that field." << std::endl;
								gamemap.setMapField('H', hero.getUnitPositionX(), hero.getUnitPositionY() - 1);
								gamemap.setMapField(' ', hero.getUnitPositionX(), hero.getUnitPositionY());
								hero.setUnitPosition(hero.getUnitPositionX(),hero.getUnitPositionY()-1);
							}
							else{
								std::cout << "The hero died during the fight(s) on that field." << std::endl;
							}
						}
					}
					else
					{
						std::cout << "Wrong input.\n";
					}
				}
			}
			else if (input == "east") {
				if (hero.getUnitPositionY() >= gamemap.getRowSize(0)-2) {
					std::cout << "Map border hit." << std::endl; ;
				}
				else
				{
					if (gamemap.getMapField(hero.getUnitPositionX(), hero.getUnitPositionY() + 1) != '#')
					{
						if (gamemap.getMapField(hero.getUnitPositionX(), hero.getUnitPositionY() + 1) == ' ') {
							gamemap.setMapField('H', hero.getUnitPositionX(), hero.getUnitPositionY() + 1);
							gamemap.setMapField(' ', hero.getUnitPositionX(), hero.getUnitPositionY());
							hero.setUnitPosition(hero.getUnitPositionX() ,hero.getUnitPositionY()+1);
						}
						else {
							gameLogAndFight(hero, monsters, hero.getUnitPositionX(), hero.getUnitPositionY() + 1);
							if(hero.isAlive()){
								std::cout << "The hero won the fights on that field." << std::endl;
								gamemap.setMapField('H', hero.getUnitPositionX(), hero.getUnitPositionY() + 1);
								gamemap.setMapField(' ', hero.getUnitPositionX(), hero.getUnitPositionY());
								hero.setUnitPosition(hero.getUnitPositionX() ,hero.getUnitPositionY()+1);
							}
							else{
								std::cout << "The hero died during the fight(s) on that field." << std::endl;
							}
						}
					}
					else
					{
						std::cout << "Wrong input.\n";
					}
				}
			}
			else {
			std::cout << "Wrong input.\n";
			}
		}
		if(hero.isAlive())
		{
			for(auto render:renderers){
				render->render(*this);
			}
			std::cout<<hero.getName()<<" cleared the map."<<std::endl;
		}
	}
}