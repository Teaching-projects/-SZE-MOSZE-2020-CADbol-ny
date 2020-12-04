#include "PreparedGame.h"
#include <iostream>

PreparedGame::PreparedGame(const std::string& filename){
    scenario=JSON::parseFromFile(filename);
}

void PreparedGame::init(){
    MarkedMap map(scenario.get<std::string>("map"));
    gamemap=map;
    hero=Hero::parse(scenario.get<std::string>("hero"));
    for(int i=0;i<gamemap.getMapSize();i++){
        for(int j=0;j<gamemap.getRowSize(i);j++){
            switch(gamemap.getMapField(i,j)){
                case '1':
                    monsters.push_back(Monster::parse(scenario.get<std::string>("monster-1")));
                    monsters.back().setUnitPosition(i,j);
                    monstercount++;
                    break;
                case '2':
                    monsters.push_back(Monster::parse(scenario.get<std::string>("monster-2")));
                    monsters.back().setUnitPosition(i,j);
                    monstercount++;
                    break;
                 case '3':
                    monsters.push_back(Monster::parse(scenario.get<std::string>("monster-3")));
                    monsters.back().setUnitPosition(i,j);
                    monstercount++;
                    break;
                case 'H':
                    hero.setUnitPosition(i,j);
                    break;
            }
        }
    }
}

void PreparedGame::run(){
    std::string input="";
    PreparedGame::init();
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
				for(auto render:renderers){
					render->render(*this);
				}
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