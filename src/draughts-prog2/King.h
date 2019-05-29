#pragma once
#include "Piece.h"

class King : public Piece
{
public:
	King(sprite);
	~King();
	bool isCrowned() const;
	operator char() const;
};
