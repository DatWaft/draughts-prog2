#pragma once
#include "Exception.h"
#include "Position.h"

class Board
{
public:
	static const size_t MAX = 8;
public:
	Position*** board;
public:
	Board();
	~Board();

	Coord search(Piece*);

	void setPiece(Coord, Piece*);
	void setPiece(size_t, size_t, Piece*);

	void capturePiece(Coord);
	void capturePiece(size_t, size_t);

	bool upgradePiece(Coord);
	bool upgradePiece(size_t, size_t);

	Piece* getPiece(Coord);
	Piece* getPiece(size_t, size_t);

	bool darkened(Coord);
	bool darkened(size_t, size_t);

	char getSprite(Coord);
	char getSprite(size_t, size_t);
};

