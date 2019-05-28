#include "Men.h"

Men::Men(sprite color): Piece(color) { }

Men::~Men() { }

bool Men::crowned() const
{
	return false;
}

Men::operator char() const
{
	if (this->black())
		return char('O');
	else
		return char('X');
}
