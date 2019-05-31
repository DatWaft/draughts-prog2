#pragma once
#include "Piece.h"

class King : public Piece
{
public:
	King(sprite, Coord = {});
	~King();
	bool isCrowned() const;
	operator char() const;
};
