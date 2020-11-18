#include "Game.h"

Game::Game(std::string filename) : gamemap(filename) {}

void Game::setMap(Map defmap){
	gamemap=defmap;
}

void Game::putHero(Hero hero, int x, int y) {
	if(!gamemap.get(x,y))
	{
		gamemap.setMapField('h',x,y);
	}
	else
	{
		throw OccupiedException("The given field is not free");
	}
	
}

void Game::putMonster(Monster monster, int x, int y) {

}