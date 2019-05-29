#include "King.h"

King::King(sprite color) : Piece(color) { }

King::~King() { }

bool King::isCrowned() const
{
	return true;
}

King::operator char() const
{
	if (this->isBlack())
		return char('N');
	else
		return char('B');
}