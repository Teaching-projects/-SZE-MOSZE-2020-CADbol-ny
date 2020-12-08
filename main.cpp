#include <iostream>
#include <map>
#include <string>
#include <filesystem>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <list>
#include <iostream>
 
#include "JSON.h"
#include "Hero.h"
#include "Monster.h"
#include "Game.h"
#include "MarkedMap.h"
#include "PreparedGame.h"
#include "Renderer.h"
#include "SVGRenderer.h"

 
 
const std::map<int,std::string> error_messages = {
    { 1 , "Bad number of arguments. Only a single scenario file should be provided." },
    { 2 , "The provided scenario file is not accessible." }
};
 
void bad_exit(int exitcode){
    std::cerr 
        << (error_messages.count(exitcode) ? error_messages.at(exitcode) : "Unknown error")
        << std::endl;
    exit(exitcode);
}
 
int main(int argc, char** argv){
    if (argc != 2) bad_exit(1);
    if (!std::filesystem::exists(argv[1])) bad_exit(2);

    /*try {
        Game gameplay("map.txt");
        std::string hero_file="";
	    std::list<std::string> monster_files = {};
        try{
            JSON scenario= JSON::parseFromFile(argv[1]);
            if (!(scenario.count("hero") && scenario.count("monsters"))) std::cerr << "JSON parsing error";
		    else {
			hero_file = scenario.get<std::string>("hero");
			JSON::list monster_file_list = scenario.get<JSON::list>("monsters");
			for (auto monster_file : monster_file_list)
				monster_files.push_back(std::get<std::string>(monster_file));
            }
        }catch (const JSON::ParseException& e) { std::cerr <<e.what()<<std::endl ; exit(0);}
        try {
            Hero hero(Hero::parse(hero_file));
            gameplay.putHero(hero,4, 3);
        }
        catch (Game::AlreadyHasHeroException& e) { std::cerr << e.what()<<std::endl;exit(0); }
        catch (Game::OccupiedException& e) { std::cerr << e.what()<<std::endl;exit(0); }
        try {
            int k=0;
            for (const auto& monster_file : monster_files) {
                Monster monster(Monster::parse(monster_file));
                if(k>=3){
                    gameplay.putMonster(monster, 5, 3);
                }
                else{
                    gameplay.putMonster(monster, 2, 1);
                }
                k++;
            }
        }catch (Game::OccupiedException& e) { std::cerr << e.what()<<std::endl;exit(0); }
        gameplay.registerRenderer(new ObserverTextRender());
        gameplay.run();
    }catch (const Game::NotInitializedException& e) { std::cerr << e.what()<<std::endl;exit(0); }*/
    try{
        PreparedGame gameplay(argv[1]);
        gameplay.registerRenderer(new HeroTextRender());
        auto out=std::ofstream("log.txt");
        gameplay.registerRenderer(new ObserverTextRender(out));
        gameplay.registerRenderer(new ObserverSVGRenderer("svg/pretty.svg"));
        gameplay.run();
    }catch (const Game::NotInitializedException& e) { std::cerr << e.what()<<std::endl;exit(0); }
    return 0;
}