#include "Men.h"

Men::Men(sprite color, Coord coord): Piece(color, coord) { }

Men::~Men() { }

bool Men::isCrowned() const
{
	return false;
}

Men::operator char() const
{
	if (this->isBlack())
		return char('O');
	else
		return char('X');
}
