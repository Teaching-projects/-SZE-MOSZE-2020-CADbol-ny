#pragma once
#include <string>
#include <vector>
#include <stdexcept>

/**
 * \class Map
 * 
 * \brief This is the class for the map.
 *  
 * 
 * 
*/
class Map {
protected:
	std::vector <std::string> map;///<This is the std::vector for the class.
	enum type{Free=0,Wall=1};///<This is the enum for the class.
public:
	///This is the default constructor for the class.
	Map(){}
	///This is a constructor for the class.
	Map(const std::string&);
	///This function checks if the given field is empty or not.
	type get(int, int) const;
	/**
	 * \class WrongIndexException
	 * 
	 * \brief This is the class for errors.
	 *  
	 * 
	 * 
	*/
	class WrongIndexException: public std::logic_error
	{
		public:	
		///This is the constructor for the class.
		WrongIndexException(const char* e) : std::logic_error(e) {}
	};
	/// Getter for the current map field.
	/// 
	/// This is a simple getter function.
	/// <returns>The character on the given field.
	char getMapField(int x,int y) const { return map[x][y];}
	///This function places a character on the given field.
	void setMapField(char chr,int x,int y){ map[x][y]=chr;}
	///This function checks if the map is empty.
	bool mapIsEmpty() { return map.empty();}
	/// Getter for the current map size.
	/// 
	/// This is a simple getter function.
	/// <returns>The map size.
	int getMapSize() const { return map.size();}
	/// Getter for the current map row size.
	/// 
	/// This is a simple getter function.
	/// <returns>The size of the given row.
	int getRowSize(int x) const { return map[x].size();}
};