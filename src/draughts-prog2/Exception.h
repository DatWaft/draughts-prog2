#pragma once
#include <string>

using std::string;

class Exception
{
private:
	string _message;
public:
	Exception(string);
	Exception(const char*);
	virtual ~Exception();
	virtual string what() const throw();
};