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
    //if (argc != 2) bad_exit(1);
    if (!std::filesystem::exists("scenario1.json")) bad_exit(2);

    try {
        Game gameplay("map.txt");
        gameplay.init("scenario1.json");
        gameplay.run();
    }
    catch (const Game::NotInitializedException& e) { std::cerr << e.what(); }
    /*try { 
        Hero hero{Hero::parse(hero_file)};
        std::list<Monster> monsters;
        for (const auto& monster_file : monster_files)
            monsters.push_back(Monster::parse(monster_file));        
 
        while (hero.isAlive() && !monsters.empty()) {
            std::cout 
                << hero.getName() << "(" << hero.getLevel()<<")"
                << " vs "
                << monsters.front().getName()
                <<std::endl;
            hero.fightTilDeath(monsters.front());
            if (!monsters.front().isAlive()) monsters.pop_front();
        }
        std::cout << (hero.isAlive() ? "The hero won." : "The hero died.") << std::endl;
        std::cout << hero.getName() << ": LVL" << hero.getLevel() << std::endl
                  << "   HP: "<<hero.getHealthPoints()<<"/"<<hero.getMaxHealthPoints()<<std::endl
                  << "  DMG: "<<hero.getDamage()<<std::endl
                  << "  ACD: "<<hero.getAttackCoolDown()<<std::endl
                  ;
    } catch (const JSON::ParseException& e) {bad_exit(4);}*/
    return 0;
}