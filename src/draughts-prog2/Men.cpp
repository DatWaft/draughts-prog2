#include "Men.h"

Men::Men(sprite color): Piece(color) { }

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
