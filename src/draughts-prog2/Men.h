#pragma once
#include "Piece.h"

class Men: public Piece
{
public:
	Men(sprite);
	~Men();
	bool isCrowned() const;
	operator char() const;
};
