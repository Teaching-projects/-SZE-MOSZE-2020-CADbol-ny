#pragma once
#include <string>
#include <vector>
#include <stdexcept>

class Map {
protected:
	std::vector <std::string> map;
	enum type{Free=0,Wall=1};
public:
	Map(){}

	Map(const std::string&);

	type get(int, int) const;

	class WrongIndexException: public std::logic_error
	{
		public:	WrongIndexException(const char* e) : std::logic_error(e) {}
	};

	char getMapField(int x,int y) const { return map[x][y];}

	int getMapSize() const { return map.size();}

	int getRowSize(int x) const { return map[x].size();}

	void setMapField(char chr,int x,int y){ map[x][y]=chr;}

	bool mapIsEmpty() { return map.empty();}

};