#pragma once
#include "Position.h"

class Board
{
private:
	Position*** board;
public:
	Board();
	~Board();

	Coord search(Piece*);

	Piece* getPiece(Coord);
	Piece* getPiece(size_t, size_t);

	char getSprite(Coord);
	char getSprite(size_t, size_t);
};

