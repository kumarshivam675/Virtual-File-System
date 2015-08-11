#include<iostream>
#include<vector>
#include<string>

#ifndef PATHSTRING_H
#define PATHSTRING_H

class PathString{
	std::string base_path;
	std::string delimiter;
public:
	PathString( std::string base, std::string delim );
	std::vector<std::string> getTokens() const;
	std::string getLast() const;
	std::string excludeLast() const;
	void printTokens() const;
	std::string getPath() const;
};

inline PathString::PathString( std::string base, std::string delim ) :
	base_path(base), delimiter(delim)
{
}

inline std::string PathString::getLast() const
{
	return(base_path.substr(base_path.rfind(delimiter)+delimiter.size(),std::string::npos));
}

inline std::string PathString::getPath() const
{
	return base_path;
}


inline std::string PathString::excludeLast() const
{
	std::string trimstring = base_path;
	trimstring.erase(base_path.rfind(delimiter),base_path.size());
	return trimstring;
}

#endif

