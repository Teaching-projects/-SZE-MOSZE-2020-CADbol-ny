#pragma once
#include <map>
#include <string>
#include <fstream>
#include <exception>
#include <any>
/**
 * \class JSON
 * 
 * \brief This is the class for the inputs.
 * 
 *  This class handles all the inputs.
*/
class JSON{
private:
	std::map<std::string, std::any> cont;///<This is the std::map for the class.
public:
	///This function handles the input file.
	static JSON parseFromFile(const std::string&);
	///This function handles the input ifstream.
	static JSON parseFromIstream(std::ifstream&);
	///This function handles the input string.
	static JSON parseFromString(std::string&);
	/// This is the parse function.
	template<typename T>
	static JSON parse(T&);
	/// This function returns the key.
	template<typename T>
	T get(const std::string& key){
		return std::any_cast<T>(cont[key]);
	}
	/// This function checks for the key.
	unsigned int count(const std::string& key){
		if(cont.find(key)==cont.end()){
			return 0;
		}
		else {
			return 1;
		}
	}
	/**
	 * \class ParseException 
	 * 
	 * \brief This class is for the errors.
	 * 
	 * 
	 * This class handles the file opening error.
	*/
	class ParseException : public std::runtime_error
	{
	public:
	///This is the constructor for the class.
		ParseException(const char* what) : runtime_error(what) {}
	};
	/// This is the constructor for the JSON class.
	JSON(std::map<std::string, std::any>cont): cont(cont)
	{}
};