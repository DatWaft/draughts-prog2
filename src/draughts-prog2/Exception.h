#pragma once
#include <string>

class Exception
{
private:
	std::string _message;
public:
	Exception(std::string);
	Exception(const char*);
	virtual ~Exception();
	virtual std::string what() const throw();
};