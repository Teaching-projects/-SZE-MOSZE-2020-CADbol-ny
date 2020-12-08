#pragma once
#include <map>
#include <string>
#include <fstream>
#include <exception>
#include <list>
#include <variant>
#include <sstream>
#include <iterator>
/**
 * \class JSON
 * 
 * \brief This is the class for the inputs.
 * 
 *  This class handles all the inputs.
*/
class JSON{
private:
	std::map<std::string,std::variant<std::string,int,float>> cont;///<This is the std::map for the class.
public:
	typedef std::list<std::variant<std::string,int,float>> list;///<This typedefinition for convenience.
	///This function handles the input file.
	static JSON parseFromFile(const std::string&);
	///This function handles the input ifstream.
	static JSON parseFromIstream(std::ifstream&);
	///This function handles the input string.
	static JSON parseFromString(std::string&);
	/// This is the parse function.
	template<typename T>
	static JSON parse(T&);
	/// This function returns the list paired with the key.
	template <typename T>
	typename std::enable_if<std::is_same<T, JSON::list>::value, T>::type
	get(const std::string& key)
	{
		list jlist;
		std::istringstream values(std::get<std::string>(cont[key]));
		std::copy(std::istream_iterator<std::string>(values),
		std::istream_iterator<std::string>(),
		std::back_inserter(jlist));
		return jlist;
	}
	/// This function returns the value paired with the key.
	template <typename T> 
	typename std::enable_if<!std::is_same<T, JSON::list>::value, T>::type
	get(const std::string& key)
	{
 		return std::get<T>(cont[key]);
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
		explicit ParseException(const char* what) : runtime_error(what) {}
	};
	/// This is the constructor for the JSON class.
	explicit JSON(const std::map<std::string, std::variant<std::string,int,float>>&cont): cont(cont)
	{}
	/// This is the desstructor for the JSON class.
	JSON(){}
};