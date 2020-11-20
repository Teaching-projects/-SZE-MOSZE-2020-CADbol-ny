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

void Game::run(){
	Game gameplay("map.txt");
	std::string input="";
	if(gameplay.gamemap.mapIsEmpty() || !gameplay.heroIsPresent()){
		throw NotInitializedException("The map is not initialized or there is no hero on it.");
	}
	else {
		/*Deps
		gameplay.putHero(Hero,x,y);
		for (const auto& monster : monsters){
			gameplay.putMonster(monster,x,y);
		}
		while(hero.isAlive() && !monsters.empty()){
			for(int i=0;i<gameplay.gamemap.getMapSize();i++){
				for(int j=0;j<gameplay.gamemap.getRowSize(i);j++){
				switch(getMapField(i,j)){
						case '#':
							std::cout<<"██";
							break;
						case ' ':
							std::cout<<"░░";
							break;
						case 'h':
							std::cout<<"┣┫";
							break;
						case 'm':
							int mult=0;
							for (const auto& monster : monsters)
							{
								if(monster.getUnitPositionX==i && monster.getUnitPositionY==j)
								{
									mult++;
								}
							}
							std::cout<< (mult>1) ? "MM" : "M░";
							break;
					}
				}
			}	
		std::cin>>input;
		switch(input){
			case "north":
				break;
			case "south":
				break;
			case "east":
				break;
			case "west":
				break;
		}
		system("cls");
		}*/
	}
}