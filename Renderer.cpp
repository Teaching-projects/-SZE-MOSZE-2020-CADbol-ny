#include "Renderer.h"
#include <iostream>

void TextRender::render(const Game& game)const{
	int mult=0;
	std::cout << "╔";
	for (int i = 0; i < game.getMap().getRowSize(0)-1; i++)
	{
		std::cout << "══";
	}
	std::cout << "╗" << std::endl;
	for (int i = 0; i < game.getMap().getMapSize(); i++) {
		std::cout << "║";
		for (int j = 0; j < game.getMap().getRowSize(i); j++) {
			switch (game.getMap().getMapField(i, j)) {
			case 'H':
				std::cout << "┣┫";
				game.getHero().setUnitPosition(i,j);
				break;
			case '#':
				std::cout << "██";
				break;
			case 'm':
				mult = 0;
				for (const auto& monster : game.getMonster())
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
			case '1':
				std::cout << "M░";
				break;
			case '2':
				std::cout << "M░";
				break;
			case '3':
				std::cout << "M░";
				break;
			}
		}
		std::cout << "║\n";
	}
	std::cout << "╚";
	for (int i = 0; i < game.getMap().getRowSize(0)-1; i++)
	{
		std::cout << "══";
	}
	std::cout << "╝" << std::endl;
}

void HeroTextRender::render(const Game& game)const{
	/*int mult=0;
	std::cout << "╔";
	for (int i = 0; i < game.getHero().getLightRadius()*2; i++)
	{
		std::cout << "══";
	}
	std::cout << "╗" << std::endl;
	for (int i = (game.getHero().getUnitPositionX()-game.getHero().getLightRadius()<= 0 ? 0:game.getHero().getUnitPositionX()-game.getHero().getLightRadius()); i < (game.getHero().getUnitPositionX()+game.getHero().getLightRadius() >=game.getMapSize()-1 ? game.getMapSize():game.getHero().getUnitPositionX()+game.getHero().getLightRadius()); i++) {
		std::cout << "║";
		for (int j = 0; j < game.getMap().getRowSize(i); j++) {
			switch (game.getMap().getMapField(i, j)) {
			case 'H':
				std::cout << "┣┫";
				game.getHero().setUnitPosition(i,j);
				break;
			case '#':
				std::cout << "██";
				break;
			case 'm':
				mult = 0;
				for (const auto& monster : game.getMonster())
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
			case '1':
				std::cout << "M░";
				break;
			case '2':
				std::cout << "M░";
				break;
			case '3':
				std::cout << "M░";
				break;
			}
		}
		std::cout << "║\n";
	}
	std::cout << "╚";
	for (int i = 0; i < game.getMap().getRowSize(0)-1; i++)
	{
		std::cout << "══";
	}
	std::cout << "╝" << std::endl;*/
	std::cout <<game.getHero().getLightRadius() << std::endl;
}