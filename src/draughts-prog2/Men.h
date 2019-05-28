#pragma once
#include "Piece.h"

class Men: public Piece
{
	Men(sprite);
	~Men();
	bool crowned() const;
	operator char() const;
};
