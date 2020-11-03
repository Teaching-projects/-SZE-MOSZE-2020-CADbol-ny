#pragma once
#include <map>
#include <string>
#include <fstream>
#include <exception>

class JSON : public std::map<std::string, std::string>{
public:
	static JSON parseFromFile(const std::string&);

	static JSON parseFromIstream(std::ifstream&);
	
	static JSON parseFromString(std::string&);
	
	template<typename T>
	static JSON parse(T&);

	class ParseException : public std::runtime_error
	{
	public:
		ParseException(const char* what) : runtime_error(what) {}
	};
};