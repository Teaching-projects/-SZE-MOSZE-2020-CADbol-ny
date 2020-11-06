#pragma once
#include <map>
#include <string>
#include <fstream>
#include <exception>
#include <any>

class JSON{
private:
	std::map<std::string, std::any> cont;
public:
	static JSON parseFromFile(const std::string&);

	static JSON parseFromIstream(std::ifstream&);
	
	static JSON parseFromString(std::string&);
	
	template<typename T>
	static JSON parse(T&);

	template<typename T>
	T get(const std::string& key){
		return std::any_cast<T>(cont[key]);
	}
	unsigned int count(const std::string& key){
		if(cont.find(key)==cont.end()){
			return 0;
		}
		else {
			return 1;
		}
	}

	class ParseException : public std::runtime_error
	{
	public:
		ParseException(const char* what) : runtime_error(what) {}
	};
	JSON(std::map<std::string, std::any> cont): cont(cont)
	{}
};