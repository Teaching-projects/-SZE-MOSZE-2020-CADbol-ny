#pragma once
#include <map>
#include <string>
#include <fstream>
/**
* \class JsonParser
*
*
*
*	This is the class that handles the .json files, which contains our units.
*	In these inputs, ones data is written in a specific order. This class can read from files, istream and string.
*	It can handle missing whitespaces or semicolons.
*
*/
class JsonParser {
public:
/**
 * This function handles the input if its a file.
*/
	static std::map< std::string, std::string> ParseFile(const std::string&);
/**
 * This function handles the input if its istream.
*/
	static std::map< std::string, std::string> ParseIstream(std::ifstream&);
/**
 * This function handles the input if its a string.
 * 
*/
	static std::map< std::string, std::string> ParseString(std::string&);
/**
 *  This is the template for the universal istream input.
*/
	template<typename T>
	static std::map<std::string, std::string> Parser(T&);
};