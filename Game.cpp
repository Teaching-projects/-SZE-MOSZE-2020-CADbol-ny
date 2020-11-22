#include "Game.h"
#include <iostream>


Game::Game(std::string filename) : gamemap(filename) {}

void Game::setMap(Map defmap){
	for(int i=0;i<defmap.getMapSize();i++){
		for(int j=0;j<defmap.getRowSize(i);j++){
			if(defmap.getMapField(i,j)=='h' || defmap.getMapField(i,j)=='m'){
				throw AlreadyHasUnitException("The map already has units, can't change it.");
			}		
		}
	}
	gamemap=defmap;
}

void Game::putHero(Hero& hero, int x, int y) {
	for(int i=0;i<gamemap.getMapSize();i++){
		for(int j=0;j<gamemap.getRowSize(i);j++){
			if(gamemap.getMapField(i,j)=='h'){
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
		gamemap.setMapField('h',x,y);
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
			if(gamemap.getMapField(i,j)=='h')
			{
				present=true;
				break;
			}	
		}
	}
	return present;
}

void Game::init(const std::string& arg) {
	try {
		JSON scenario = JSON::parseFromFile(arg);
		if (!(scenario.count("hero") && scenario.count("monsters"))) std::cerr << "JSON parsing error";
		else {
			hero_file = scenario.get<std::string>("hero");
			JSON::list monster_file_list = scenario.get<JSON::list>("monsters");
			for (auto monster_file : monster_file_list)
				monster_files.push_back(std::get<std::string>(monster_file));
		}
	}
	catch (const JSON::ParseException& e) { std::cerr <<e.what() ; }
}

void Game::gameLogAndFight(Hero& hero, std::list<Monster>& monsters,int x,int y) {
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

void Game::run(){
	std::string input="";
	if(gamemap.mapIsEmpty()){ //|| !Game::heroIsPresent()){
		throw NotInitializedException("The map is not initialized or there is no hero on it.");
	}
	else {
		try {
			Hero hero{ Hero::parse(hero_file) };
			std::list<Monster> monsters;
			for (const auto& monster_file : monster_files)
				monsters.push_back(Monster::parse(monster_file));
			monstercount=monsters.size();
			try {
				try {
					putHero(hero, 0, 0);
				}
				catch (Game::AlreadyHasHeroException& e) { std::cerr << e.what()<<std::endl;exit(0); }
			}
			catch (Game::OccupiedException& e) { std::cerr << e.what()<<std::endl;exit(0); }
			try {
				int k=0;
				for (auto& monster : monsters) {
					if(k>=3){
					putMonster(monster, 5, 3);
					}
					else{
						putMonster(monster, 2, 1);
					}
					k++;
				}
			}
			catch (Game::OccupiedException& e) { std::cerr << e.what()<<std::endl;exit(0); }
			std::string input = "";
			int mult;
			while (hero.isAlive() && monstercount!=0) {
				std::cout << "╔";
				for (int i = 0; i < gamemap.getRowSize(0)-1; i++)
				{
					std::cout << "══";
				}
				std::cout << "╗" << std::endl;
				for (int i = 0; i < gamemap.getMapSize(); i++) {
					std::cout << "║";
					for (int j = 0; j < gamemap.getRowSize(i); j++) {
						switch (gamemap.getMapField(i, j)) {
						case 'h':
							std::cout << "┣┫";
							hero.setUnitPosition(i, j);
							break;
						case '#':
							std::cout << "██";
							break;
						case 'm':
							mult = 0;
							for (const auto& monster : monsters)
							{
								if (monster.getUnitPositionX() == i && monster.getUnitPositionY() == j)
								{
									mult++;
								}
							}
							if (mult > 1) {
								std::cout << "MM";
							}
							else {
								std::cout << "M░";
							}
							break;
						case ' ':
							std::cout << "░░";
							break;
						}
					}
					std::cout << "║\n";
				}
				std::cout << "╚";
				for (int i = 0; i < gamemap.getRowSize(0)-1; i++)
				{
					std::cout << "══";
				}
				std::cout << "╝" << std::endl;
				std::cout << "Set input direction:";
				std::cin >> input;
				if (input == "north") {
					if (hero.getUnitPositionX() - 1 <= 0) {
						std::cout << "Map border hit." << std::endl; ;
					}
					else {
						if (gamemap.getMapField(hero.getUnitPositionX() - 1, hero.getUnitPositionY()) == ' ' || gamemap.getMapField(hero.getUnitPositionX() - 1, hero.getUnitPositionY()) == 'm')
						{
							if (gamemap.getMapField(hero.getUnitPositionX() - 1, hero.getUnitPositionY()) == ' '){
								gamemap.setMapField('h', hero.getUnitPositionX() - 1, hero.getUnitPositionY());
								gamemap.setMapField(' ', hero.getUnitPositionX(), hero.getUnitPositionY());
							}
							else{
								gameLogAndFight(hero, monsters, hero.getUnitPositionX()-1, hero.getUnitPositionY());
								if(hero.isAlive()){
									std::cout << "The hero won the fights on that field." << std::endl;
									gamemap.setMapField('h', hero.getUnitPositionX()-1, hero.getUnitPositionY());
									gamemap.setMapField(' ', hero.getUnitPositionX(), hero.getUnitPositionY());
								}
								else{
									std::cout << "The hero died during the fight(s) on that field." << std::endl;
								}
							}
						}
						else
						{
							std::cout << "Wrong input\n";
						}
					}
				}
				else if (input == "south") {
					if (hero.getUnitPositionX() + 1 >= gamemap.getMapSize()) {
						std::cout << "Map border hit." << std::endl; ;
					}
					else {
						if (gamemap.getMapField(hero.getUnitPositionX() + 1, hero.getUnitPositionY()) == ' ' || gamemap.getMapField(hero.getUnitPositionX() + 1, hero.getUnitPositionY()) == 'm')
						{
							if (gamemap.getMapField(hero.getUnitPositionX() + 1, hero.getUnitPositionY()) == ' '){
								gamemap.setMapField('h', hero.getUnitPositionX() + 1, hero.getUnitPositionY());
								gamemap.setMapField(' ', hero.getUnitPositionX(), hero.getUnitPositionY());
							}
							else{
								gameLogAndFight(hero, monsters, hero.getUnitPositionX()+1, hero.getUnitPositionY());
								if(hero.isAlive()){
									std::cout << "The hero won the fights on that field." << std::endl;
									gamemap.setMapField('h', hero.getUnitPositionX()+1, hero.getUnitPositionY());
									gamemap.setMapField(' ', hero.getUnitPositionX(), hero.getUnitPositionY());
								}
								else{
									std::cout << "The hero died during the fight(s) on that field." << std::endl;
								}
							}
						}
						else
						{
							std::cout << "Wrong input\n";
						}
					}
				}
				else if (input == "west") {
					if (hero.getUnitPositionY() - 1 <= 0) {
						std::cout << "Map border hit." << std::endl; ;
					}
					else {
						if (gamemap.getMapField(hero.getUnitPositionX(), hero.getUnitPositionY() - 1) == ' ' || gamemap.getMapField(hero.getUnitPositionX(), hero.getUnitPositionY() - 1) == 'm')
						{
							if (gamemap.getMapField(hero.getUnitPositionX(), hero.getUnitPositionY() - 1) == ' '){
							gamemap.setMapField('h', hero.getUnitPositionX(), hero.getUnitPositionY() - 1);
							gamemap.setMapField(' ', hero.getUnitPositionX(), hero.getUnitPositionY());
							}
							else{
								gameLogAndFight(hero, monsters, hero.getUnitPositionX(), hero.getUnitPositionY() - 1);
								if(hero.isAlive()){
									std::cout << "The hero won the fights on that field." << std::endl;
									gamemap.setMapField('h', hero.getUnitPositionX(), hero.getUnitPositionY() - 1);
									gamemap.setMapField(' ', hero.getUnitPositionX(), hero.getUnitPositionY());
								}
								else{
									std::cout << "The hero died during the fight(s) on that field." << std::endl;
								}
							}
						}
						else
						{
							std::cout << "Wrong input";
						}
					}
				}
				else if (input == "east") {
					if (hero.getUnitPositionY() + 1 >= gamemap.getRowSize(0)) {
						std::cout << "Map border hit." << std::endl; ;
					}
					else
					{
						if (gamemap.getMapField(hero.getUnitPositionX(), hero.getUnitPositionY() + 1) == ' ' || gamemap.getMapField(hero.getUnitPositionX(), hero.getUnitPositionY() + 1) == 'm')
						{
							if (gamemap.getMapField(hero.getUnitPositionX(), hero.getUnitPositionY() + 1) == ' ') {
								gamemap.setMapField('h', hero.getUnitPositionX(), hero.getUnitPositionY() + 1);
								gamemap.setMapField(' ', hero.getUnitPositionX(), hero.getUnitPositionY());
							}
							else {
								gameLogAndFight(hero, monsters, hero.getUnitPositionX(), hero.getUnitPositionY() + 1);
								if(hero.isAlive()){
									std::cout << "The hero won the fights on that field." << std::endl;
									gamemap.setMapField('h', hero.getUnitPositionX(), hero.getUnitPositionY() + 1);
									gamemap.setMapField(' ', hero.getUnitPositionX(), hero.getUnitPositionY());
								}
								else{
									std::cout << "The hero died during the fight(s) on that field." << std::endl;
								}
							}
						}
						else
						{
							std::cout << "Wrong input\n";
						}
					}
				}
			}
			if(hero.isAlive())
			{
				std::cout<<hero.getName()<<" cleared the map."<<std::endl;
			}
		}catch(const JSON::ParseException& e) { std::cerr << e.what(); }
	}
}