#include "King.h"

King::King(sprite color) : Piece(color) { }

King::~King() { }

bool King::crowned() const
{
	return true;
}

King::operator char() const
{
	if (this->black())
		return char('N');
	else
		return char('B');
}