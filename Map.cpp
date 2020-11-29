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
		throw WrongIndexException("Index was out of range. Must be non-negative and less than the size of the vector");
	}
	if(y>map[x].size()-1 || x<0){
		throw WrongIndexException("Index was out of range. Must be non-negative and less than the size of the string");
	}
	return map[x][y]=='#' ? Wall : Free;
}