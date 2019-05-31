#pragma once
#include <iostream>
#include <string>

using std::ostream;
using std::string;
using std::to_string;

struct Coord
{
	int i{ 0 };
	int j{ 0 };

	operator bool() const;
	operator string() const;

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
