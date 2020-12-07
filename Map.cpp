#include "Map.h"
#include <fstream>

Map::Map(const std::string& filename){
	std::string line;
	std::ifstream file(filename);
	while (std::getline(file, line)){
		map.push_back(line);
		line = "";
	}
}
Map::type Map::get(int x,int y) const {
	if(x>map.size()-1 || x<0){
		throw WrongIndexException("Index was out of range. Must be non-negative and less than the size of the column.");
	}
	if(y>map[x].size()-1 || x<0){
		throw WrongIndexException("Index was out of range. Must be non-negative and less than the size of the row.");
	}
	return map[x][y]=='#' ? Wall : Free;
}