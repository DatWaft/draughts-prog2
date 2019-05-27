#include "Exception.h"

Exception::Exception(std::string string) : _message(string) {}

Exception::Exception(const char* string) : _message(string) {}

Exception::~Exception() {}

std::string Exception::what() const throw() { return _message; }
