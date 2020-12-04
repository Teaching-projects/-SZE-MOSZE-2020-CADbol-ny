#pragma once
#include <fstream>
#include "Map.h"
#include "units.h"
#include <list>

/**
 * \class MarkedMap
 * 
 * \brief This is the class for the MarkedMap.
 *  
 * 
 * 
*/

class MarkedMap: public Map {
public:
    ///This is the default constructor for the class.
    MarkedMap(){}
    ///This is a constructor for the class.
    MarkedMap(const std::string&);
protected:
    ///This function returns the hero's position.
    position getHeroPosition() const;
    ///This function returns monster positions.
    std::list<position> getMonsterPositions(char c) const;
};
