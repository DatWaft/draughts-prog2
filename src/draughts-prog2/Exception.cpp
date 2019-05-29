#include "Exception.h"

Exception::Exception(string string) : _message(string) {}

Exception::Exception(const char* string) : _message(string) {}

Exception::~Exception() {}

string Exception::what() const throw() { return _message; }
