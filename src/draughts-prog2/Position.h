#pragma once
#include "Coord.h"
#include "Men.h"
#include "King.h"

class Piece;

class Position
{
private:
	Coord coord;
	Piece* piece;
public:
	Position(Coord);
	Position(size_t, size_t);
	~Position();

	void setPiece(Piece*);
	Piece* getPiece();
	bool darkened();

	Coord getCoord();
	size_t getI();
	size_t getJ();
};

