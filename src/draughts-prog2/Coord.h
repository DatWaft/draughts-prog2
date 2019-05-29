#pragma once
#include <iostream>

using std::ostream;

struct Coord
{
	size_t i{ 0 };
	size_t j{ 0 };
	friend ostream& operator << (ostream&, const Coord&);
};
