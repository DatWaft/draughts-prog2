#include "Coord.h"

Coord Coord::invert()
{
	return Coord{-this->i, -this->j};
}

Coord::operator bool() const
{
	return i <= 8 && i > 0 && j <= 8 && j > 0;
}

Coord::operator string() const
{
	return to_string(i) + to_string(j);
}

void Coord::operator =(const Coord& pos)
{
	this->i = pos.i;
	this->j = pos.j;
}

bool Coord::operator==(const Coord& pos)
{
	return this->i == pos.i && this->j == pos.j;
}

bool Coord::operator!=(const Coord& pos)
{
	return !(*this == pos);
}

Coord Coord::operator +(const Coord& pos)
{
	return { this->i + pos.i, this->j + pos.j };
}

Coord Coord::operator -(const Coord& pos)
{
	return { this->i - pos.i, this->j - pos.j };
}

void Coord::operator +=(const Coord& pos)
{
	*this = *this + pos;
}

void Coord::operator-=(const Coord& pos)
{
	*this = *this - pos;
}

Coord Coord::operator+(const int& n)
{
	return { this->i + n, this->j + n };
}

Coord Coord::operator-(const int& n)
{
	return { this->i - n, this->j - n };
}

void Coord::operator+=(const int& n)
{
	*this = *this + n;
}

void Coord::operator-=(const int& n)
{
	*this = *this - n;
}

ostream& operator<<(ostream& out, const Coord& coord)
{
	out << "[" << coord.i << "," << coord.j << "]";
	return out;
}