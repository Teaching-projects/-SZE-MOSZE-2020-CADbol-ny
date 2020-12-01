#pragma once
#include "Game.h"
#include "JSON.h"
#include "MarkedMap.h"

class PreparedGame: public Game,MarkedMap{
private:
    JSON scenario;
public:
    PreparedGame(const std::string&);

    void init();
};