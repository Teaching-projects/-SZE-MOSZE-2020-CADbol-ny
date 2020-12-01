#include "MarkedMap.h"

MarkedMap::MarkedMap(const std::string& filename){
    std::string line;
	std::ifstream file(filename);
	while (std::getline(file, line)){
		map.push_back(line);
		line = "";
	}
}

position MarkedMap::getHeroPosition() const{
    position pos;
    for(int i=0;i<map.size();i++){
        for(int j=0;j<map[i].size();j++){
            if(map[i][j]=='H'){
                pos.x=i;
                pos.y=j;
            }
        }
    } 
    return pos;
}

std::list<position> MarkedMap::getMonsterPositions(char c) const{
    std::list<position> positions;
    position pos;
     for(int i=0;i<map.size();i++){
        for(int j=0;j<map[i].size();j++){
            if(map[i][j]==c){
                pos.x=i;
                pos.y=j;
                positions.push_back(pos);
            }
        }
     }
     return positions;
}