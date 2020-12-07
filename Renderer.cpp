#include "Renderer.h"

void ObserverTextRender::render(const Game& game)const{
	int mult=0;
	*output << "╔";
	for (int i = 0; i < game.getMap().getRowSize(0)-1; i++)
	{
		*output << "══";
	}
	*output << "╗" << std::endl;
	for (int i = 0; i < game.getMap().getMapSize(); i++) {
		*output << "║";
		for (int j = 0; j < game.getMap().getRowSize(i); j++) {
			switch (game.getMap().getMapField(i, j)) {
			case 'H':
				*output << "┣┫";
				break;
			case '#':
				*output << "██";
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
					*output << "MM";
				}
				else {
					*output << "M░";
				}
				break;
			case ' ':
				*output << "░░";
				break;
			case '1':
				*output << "M░";
				break;
			case '2':
				*output << "M░";
				break;
			case '3':
				*output << "M░";
				break;
			}
		}
		*output << "║\n";
	}
	*output << "╚";
	for (int i = 0; i < game.getMap().getRowSize(0)-1; i++)
	{
		*output << "══";
	}
	*output << "╝" << std::endl;
}

void HeroTextRender::render(const Game& game)const{
	int mult=0;
	*output<<"╔";
	for (int j = (game.getHero().getUnitPositionY()-game.getHero().getLightRadius()<0 ? 0: game.getHero().getUnitPositionY()-game.getHero().getLightRadius()); j <= (game.getHero().getUnitPositionY()+game.getHero().getLightRadius()>=game.getGameMapRowSize(0)-1 ? game.getGameMapRowSize(0)-2:game.getHero().getUnitPositionY()+game.getHero().getLightRadius()); j++)
	{
		*output << "══";
	}
	*output << "╗" << std::endl;
	for (int i =(game.getHero().getUnitPositionX()-game.getHero().getLightRadius()<0 ? 0: game.getHero().getUnitPositionX()-game.getHero().getLightRadius());i<=(game.getHero().getUnitPositionX()+game.getHero().getLightRadius()>=game.getGameMapSize()? game.getGameMapSize()-1:game.getHero().getUnitPositionX()+game.getHero().getLightRadius()); i++) {
		*output << "║";
		for (int j = (game.getHero().getUnitPositionY()-game.getHero().getLightRadius()<0 ? 0: game.getHero().getUnitPositionY()-game.getHero().getLightRadius()); j <= (game.getHero().getUnitPositionY()+game.getHero().getLightRadius()>=game.getGameMapRowSize(i) ? game.getGameMapRowSize(i)-1:game.getHero().getUnitPositionY()+game.getHero().getLightRadius()); j++){
			switch (game.getMap().getMapField(i, j)) {
			case 'H':
				*output << "┣┫";
				break;
			case '#':
				*output << "██";
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
					*output << "MM";
				}
				else {
					*output << "M░";
				}
				break;
			case ' ':
				*output << "░░";
				break;
			case '1':
				*output << "M░";
				break;
			case '2':
				*output << "M░";
				break;
			case '3':
				*output << "M░";
				break;
			}
		}
		*output << "║\n";
	}
	*output << "╚";
	for (int j = (game.getHero().getUnitPositionY()-game.getHero().getLightRadius()<0 ? 0: game.getHero().getUnitPositionY()-game.getHero().getLightRadius()); j <= (game.getHero().getUnitPositionY()+game.getHero().getLightRadius()>=game.getGameMapRowSize(0)-1 ? game.getGameMapRowSize(0)-2:game.getHero().getUnitPositionY()+game.getHero().getLightRadius()); j++)
	{
		*output << "══";
	}
	*output << "╝" << std::endl;
}
TextRender::TextRender(std::ostream& out){
		output=&out;
}
void TextRender::setOutputStream(std::ostream& out){
		output=&out;
}