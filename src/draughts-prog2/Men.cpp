#include "Men.h"

Men::Men(sprite color, Position* position) : Piece(color, position) { }

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
