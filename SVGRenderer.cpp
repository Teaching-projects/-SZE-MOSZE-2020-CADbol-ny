#include "SVGRenderer.h"
#include <fstream>

void ObserverSVGRenderer::render(const Game& game)const{
    std::ofstream file(filename);
	file<<"<svg xmlns=\"http://www.w3.org/2000/svg\">";
	for (int i = 0; i < game.getMap().getMapSize(); i++) {
		for (int j = 0; j < game.getMap().getRowSize(i); j++) {
			switch (game.getMap().getMapField(i, j)) {
			case 'H':
				file << "<image x=\""<<(j+1)*100<<"\" y=\""<<(i+1)*100<<"\"  width=\"100\" height=\"100\" href=\""<<game.GetHeroTexture()<<"\"></image>";
				break;
			case '#':
				file << "<image x=\""<<(j+1)*100<<"\" y=\""<<(i+1)*100<<"\"  width=\"100\" height=\"100\" href=\""<<const_cast<Game&>(game).getWallTexture()<<"\"></image>";
				break;
			case ' ':
				file << "<image x=\""<<(j+1)*100<<"\" y=\""<<(i+1)*100<<"\"  width=\"100\" height=\"100\" href=\""<<const_cast<Game&>(game).getFreeTexture()<<"\"></image>";
				break;
			case '1':
				file << "<image x=\""<<(j+1)*100<<"\" y=\""<<(i+1)*100<<"\"  width=\"100\" height=\"100\" href=\""<<const_cast<Game&>(game).getMonsterTexture('1')<<"\"></image>";
				break;
			case '2':
				file << "<image x=\""<<(j+1)*100<<"\" y=\""<<(i+1)*100<<"\"  width=\"100\" height=\"100\" href=\""<<const_cast<Game&>(game).getMonsterTexture('2')<<"\"></image>";
				break;
			case '3':
				file << "<image x=\""<<(j+1)*100<<"\" y=\""<<(i+1)*100<<"\"  width=\"100\" height=\"100\" href=\""<<const_cast<Game&>(game).getMonsterTexture('3')<<"\"></image>";
				break;
			}
		}
	}
	file<<"</svg>";
    file.close();
}

void CharacterSVGRenderer::render(const Game& game)const{
    std::ofstream file(filename);
	file<<"<svg xmlns=\"http://www.w3.org/2000/svg\">";
	for (int i =(game.getHero().getUnitPositionX()-game.getHero().getLightRadius()<0 ? 0: game.getHero().getUnitPositionX()-game.getHero().getLightRadius());i<=(game.getHero().getUnitPositionX()+game.getHero().getLightRadius()>=game.getGameMapSize()? game.getGameMapSize()-1:game.getHero().getUnitPositionX()+game.getHero().getLightRadius()); i++) {
		for (int j = (game.getHero().getUnitPositionY()-game.getHero().getLightRadius()<0 ? 0: game.getHero().getUnitPositionY()-game.getHero().getLightRadius()); j <= (game.getHero().getUnitPositionY()+game.getHero().getLightRadius()>=game.getGameMapRowSize(i) ? game.getGameMapRowSize(i)-1:game.getHero().getUnitPositionY()+game.getHero().getLightRadius()); j++){
			switch (game.getMap().getMapField(i, j)) {
			case 'H':
				file << "<image x=\""<<(j+1)*100<<"\" y=\""<<(i+1)*100<<"\"  width=\"100\" height=\"100\" href=\""<<game.GetHeroTexture()<<"\"></image>";
				break;
			case '#':
				file << "<image x=\""<<(j+1)*100<<"\" y=\""<<(i+1)*100<<"\"  width=\"100\" height=\"100\" href=\""<<const_cast<Game&>(game).getWallTexture()<<"\"></image>";
				break;
			case ' ':
				file << "<image x=\""<<(j+1)*100<<"\" y=\""<<(i+1)*100<<"\"  width=\"100\" height=\"100\" href=\""<<const_cast<Game&>(game).getFreeTexture()<<"\"></image>";
				break;
			case '1':
				file << "<image x=\""<<(j+1)*100<<"\" y=\""<<(i+1)*100<<"\"  width=\"100\" height=\"100\" href=\""<<const_cast<Game&>(game).getMonsterTexture('1')<<"\"></image>";
				break;
			case '2':
				file << "<image x=\""<<(j+1)*100<<"\" y=\""<<(i+1)*100<<"\"  width=\"100\" height=\"100\" href=\""<<const_cast<Game&>(game).getMonsterTexture('2')<<"\"></image>";
				break;
			case '3':
				file << "<image x=\""<<(j+1)*100<<"\" y=\""<<(i+1)*100<<"\"  width=\"100\" height=\"100\" href=\""<<const_cast<Game&>(game).getMonsterTexture('3')<<"\"></image>";
				break;
			}
		}
	}
    file<<"</svg>";
    file.close();
}