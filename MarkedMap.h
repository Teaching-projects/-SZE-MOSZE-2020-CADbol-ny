#pragma once
#include <fstream>
#include "Map.h"
#include "units.h"
#include <list>

class MarkedMap: public Map {
public:
    MarkedMap(){}
    MarkedMap(const std::string&);
protected:
    position getHeroPosition() const;

    std::list<position> getMonsterPositions(char c) const;
};
