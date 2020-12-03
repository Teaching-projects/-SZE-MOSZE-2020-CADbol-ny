#include <iostream>
#include <map>
#include <string>
#include <filesystem>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <list>
 
#include "JSON.h"
#include "Hero.h"
#include "Monster.h"
#include "Game.h"
#include "MarkedMap.h"
#include "PreparedGame.h"
#include "Renderer.h"

 
 
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
        gameplay.init(argv[1]);
        try {
            gameplay.putHero(gameplay.getHero(),5, 5);
        }
        catch (Game::AlreadyHasHeroException& e) { std::cerr << e.what()<<std::endl;exit(0); }
        catch (Game::OccupiedException& e) { std::cerr << e.what()<<std::endl;exit(0); }
        try {
            int k=0;
            for (auto& monster : gameplay.getMonster()) {
                if(k>=3){
                gameplay.putMonster(monster, 5, 3);
                }
                else{
                    gameplay.putMonster(monster, 2, 1);
                }
                k++;
            }
        }catch (Game::OccupiedException& e) { std::cerr << e.what()<<std::endl;exit(0); }
        gameplay.run();
    }catch (const Game::NotInitializedException& e) { std::cerr << e.what()<<std::endl;exit(0); }*/
    try{
        PreparedGame gameplay(argv[1]);
        gameplay.run();  
    }catch (const Game::NotInitializedException& e) { std::cerr << e.what()<<std::endl;exit(0); }
    return 0;
}