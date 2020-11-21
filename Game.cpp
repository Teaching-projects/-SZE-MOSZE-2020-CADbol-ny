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

void Game::putHero(Hero hero, int x, int y) {
	for(int i=0;i<gamemap.getMapSize();i++){
		for(int j=0;j<gamemap.getRowSize(i);j++){
			if(gamemap.getMapField(i,j)=='h'){
				throw AlreadyHasHeroException("There is already a hero on the map, can't place an other one.");
			}
		}
	}
	if(gamemap.get(x,y)==Wall)
	{
		throw OccupiedException("The given field is not free");
	}
	else
	{
		gamemap.setMapField('h',x,y);
		hero.setUnitPosition(x,y);
	}
	
}

void Game::putMonster(Monster monster, int x, int y) {
	if(gamemap.get(x,y)==Wall)
	{
		throw OccupiedException("The given field is not free");
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

void Game::run(){
	std::string input="";
	if(gamemap.mapIsEmpty()){ //|| !Game::heroIsPresent()){
		throw NotInitializedException("The map is not initialized or there is no hero on it.");
	}
	else {
		try {
			_setmode(_fileno(stdout), _O_U16TEXT);
			Hero hero{ Hero::parse(hero_file) };
			std::list<Monster> monsters;
			for (const auto& monster_file : monster_files)
				monsters.push_back(Monster::parse(monster_file));
			try {
				try {
					putHero(hero, 5, 1);
				}
				catch (Game::AlreadyHasHeroException& e) { std::cerr << e.what(); }
			}
			catch (Game::OccupiedException& e) { std::cerr << e.what(); }
			try {
				for (const auto& monster : monsters) {
					putMonster(monster, 1, 2);
				}
			}
			catch (Game::OccupiedException& e) { std::cerr << e.what(); }
			std::string input = "";
			int mult;
			while (hero.isAlive() && !monsters.empty()) {
				std::wcout << L"\u2554";
				for (int i = 0; i < gamemap.getRowSize(0); i++)
				{
					std::wcout << L"\u2550\u2550";
				}
				std::wcout << L"\u2557" << std::endl;
				for (int i = 0; i < gamemap.getMapSize(); i++) {
					std::wcout << L"\u2551";
					for (int j = 0; j < gamemap.getRowSize(i); j++) {
						switch (gamemap.getMapField(i, j)) {
						case 'h':
							std::wcout << L"\u2520\u2525";
							hero.setUnitPosition(i, j);
							break;
						case '#':
							std::wcout << L"\u2588\u2588";
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
								std::wcout << "MM";
							}
							else {
								std::wcout << L"M\u2592";
							}
							break;
						case ' ':
							std::wcout << L"\u2592\u2592";
							break;
						}
					}
					std::wcout << L"\u2551\n";
				}
				std::wcout << L"\u255A";
				for (int i = 0; i < gamemap.getRowSize(0); i++)
				{
					std::wcout << L"\u2550\u2550";
				}
				std::wcout << L"\u255D" << std::endl;
				std::wcout << "Set input direction:";
				std::cin >> input;
				if (input == "north") {
					if (gamemap.getMapField(hero.getUnitPositionX()- 1,hero.getUnitPositionY()) == ' ')
					{
						gamemap.setMapField('h',hero.getUnitPositionX() - 1,hero.getUnitPositionY());
						gamemap.setMapField(' ', hero.getUnitPositionX(), hero.getUnitPositionY());
					}
					else
					{
						std::wcout << "Wrong input";
					}
				}
				else if (input == "south") {
					if (gamemap.getMapField(hero.getUnitPositionX() + 1, hero.getUnitPositionY()) == ' ')
					{
						gamemap.setMapField('h', hero.getUnitPositionX() + 1, hero.getUnitPositionY());
						gamemap.setMapField(' ', hero.getUnitPositionX(), hero.getUnitPositionY());
					}
					else
					{
						std::wcout << "Wrong input";
					}
				}
				else if (input == "west") {
					if (gamemap.getMapField(hero.getUnitPositionX(), hero.getUnitPositionY()-1) == ' ')
					{
						gamemap.setMapField('h', hero.getUnitPositionX(), hero.getUnitPositionY()-1);
						gamemap.setMapField(' ', hero.getUnitPositionX(), hero.getUnitPositionY());
					}
					else
					{
						std::wcout << "Wrong input";
					}
				}
				else if (input == "east") {
					if (gamemap.getMapField(hero.getUnitPositionX(), hero.getUnitPositionY()+1) == ' ')
					{
						gamemap.setMapField('h', hero.getUnitPositionX(), hero.getUnitPositionY()+1);
						gamemap.setMapField(' ', hero.getUnitPositionX(), hero.getUnitPositionY());
					}
					else
					{
						std::wcout << "Wrong input";
					}
				}
				system("cls");
			}
		}catch(const JSON::ParseException& e) { std::cerr << e.what(); }
	}
}