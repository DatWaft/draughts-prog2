#pragma once
#include "Piece.h"

class King : public Piece
{
	King(sprite);
	~King();
	bool crowned() const;
	operator char() const;
};
