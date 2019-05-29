#pragma once
#include <iostream>
#include "Men.h"
#include "King.h"

using std::ostream;

struct Coord
{
	size_t i{ 0 };
	size_t j{ 0 };
	friend ostream& operator << (ostream&, const Coord&);
};

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

