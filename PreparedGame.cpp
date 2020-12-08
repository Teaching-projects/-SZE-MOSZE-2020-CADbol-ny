#include "PreparedGame.h"
#include <iostream>

PreparedGame::PreparedGame(const std::string& filename){
    try{
        scenario=JSON::parseFromFile(filename);
    }catch (const JSON::ParseException& e) { std::cerr <<e.what()<<std::endl ; exit(0);}
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
    PreparedGame::init();
	Game::run();
}