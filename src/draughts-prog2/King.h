#pragma once
#include "Piece.h"

class King : public Piece
{
	King(sprite);
	~King();
	bool isCrowned() const;
	operator char() const;
};
