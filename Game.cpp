#include "Game.h"
#include <iostream>


Game::Game(const std::string& filename) : gamemap(filename) {}

void Game::setMap(Map defmap){
	for(int i=0;i<defmap.getMapSize();i++){
		for(int j=0;j<defmap.getRowSize(i);j++){
			if(defmap.getMapField(i,j)=='H' || defmap.getMapField(i,j)=='m'){
				throw AlreadyHasUnitException("The map already has units, can't change it.");
			}		
		}
	}
	gamemap=defmap;
}

void Game::putHero(Hero& hero, int x, int y) {
	for(int i=0;i<gamemap.getMapSize();i++){
		for(int j=0;j<gamemap.getRowSize(i);j++){
			if(gamemap.getMapField(i,j)=='H'){
				throw AlreadyHasHeroException("There is already a hero on the map, can't place an other one.");
			}
		}
	}
	if(gamemap.get(x,y)==Wall)
	{
		throw OccupiedException("The given field is not free.");
	}
	else
	{
		gamemap.setMapField('H',x,y);
		hero.setUnitPosition(x,y);
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
	}
}

bool Game::heroIsPresent() {
	bool present=false;
	for(int i=0;i<gamemap.getMapSize();i++){
		for(int j=0;j<gamemap.getRowSize(i);j++){
			if(gamemap.getMapField(i,j)=='H')
			{
				present=true;
				break;
			}	
		}
	}
	return present;
}

void Game::init(const std::string& arg) {
	std::string hero_file="";
	std::list<std::string> monster_files = {};
	try {
		JSON scenario = JSON::parseFromFile(arg);
		if (!(scenario.count("hero") && scenario.count("monsters"))) std::cerr << "JSON parsing error";
		else {
			hero_file = scenario.get<std::string>("hero");
			JSON::list monster_file_list = scenario.get<JSON::list>("monsters");
			for (auto monster_file : monster_file_list)
				monster_files.push_back(std::get<std::string>(monster_file));
		}
		hero=Hero::parse(hero_file);
		for (const auto& monster_file : monster_files)
			monsters.push_back(Monster::parse(monster_file));
		monstercount=monsters.size();
	}
	catch (const JSON::ParseException& e) { std::cerr <<e.what()<<std::endl ; exit(0);}
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
	std::string input="";
	if(gamemap.mapIsEmpty() || !Game::heroIsPresent()){
		throw NotInitializedException("The map is not initialized or there is no hero on it.");
	}
	else {
			std::string input = "";
			bool samefield=false;
			for(auto& monster:monsters){
				if(monster.getUnitPositionX()==hero.getUnitPositionX() && monster.getUnitPositionY()==hero.getUnitPositionY())
				{
					samefield=true;
					break;
				}
			}
			if(samefield){
			gameLogAndFight(hero, monsters, hero.getUnitPositionX(), hero.getUnitPositionY());
				if(hero.isAlive()){
					std::cout << "The hero won the fights on that field." << std::endl;
					gamemap.setMapField('h', hero.getUnitPositionX(), hero.getUnitPositionY());
				}
				else{
					std::cout << "The hero died during the fight(s) on that field." << std::endl;
					exit(0);
				}
			}
			while (hero.isAlive() && monstercount!=0) {
				std::cout << "Set input direction:";
				std::cin >> input;
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
									hero.setUnitPosition(hero.getUnitPositionX() ,hero.getUnitPositionY()-1);
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
				std::cout<<hero.getName()<<" cleared the map."<<std::endl;
			}
	}
}