#include "Game.h"

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
	if(!gamemap.get(x,y))
	{
		gamemap.setMapField('h',x,y);
		hero.setUnitPosition(x,y);
	}
	else
	{
		throw OccupiedException("The given field is not free");
	}
}

void Game::putMonster(Monster monster, int x, int y) {
if(!gamemap.get(x,y))
	{
		gamemap.setMapField('m',x,y);
		monster.setUnitPosition(x,y);
	}
	else
	{
		throw OccupiedException("The given field is not free");
	}
}

void Game::run(){
	if(gamemap.mapIsEmpty()){
		throw NotInitializedException("The map is not initialized.");
	}
	else {
		
	}
}