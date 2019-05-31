#pragma once
#include "Coord.h"
#include "Men.h"
#include "King.h"

class Position
{
private:
	Coord coord;
	Piece* piece;
public:
	Position(Coord);
	Position(int, int);
	~Position();

	Piece* setPiece(Piece*);
	Piece* getPiece();
	bool darkened();

	Coord getCoord();
	int getI();
	int getJ();
};

