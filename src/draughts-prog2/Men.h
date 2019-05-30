#pragma once
#include "Piece.h"

class Men: public Piece
{
public:
	Men(sprite, Position*);
	~Men();
	bool isCrowned() const;
	operator char() const;
};
