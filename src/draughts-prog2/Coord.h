#pragma once
#include <iostream>

using std::ostream;

struct Coord
{
	size_t i{ 0 };
	size_t j{ 0 };

	void operator =(const Coord&);
	bool operator ==(const Coord&);
	bool operator !=(const Coord&);

	Coord operator +(const Coord&);
	Coord operator -(const Coord&);
	void operator +=(const Coord&);
	void operator -=(const Coord&);

	Coord operator +(const int&);
	Coord operator -(const int&);
	void operator +=(const int&);
	void operator -=(const int&);

	friend ostream& operator << (ostream&, const Coord&);
};
