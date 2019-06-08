#pragma once
#include "Exception.h"
#include "Position.h"
#include "List.h"

class Board
{
public:
	static const int MAX = 8;
private:
	Position*** board;
public:
	Board();
	~Board();

	Coord search(Piece*);

	bool movePiece(Coord, Coord);

	void setPiece(Coord, Piece*);
	void setPiece(int, int, Piece*);

	void capturePieces(List<Coord>);
	void capturePiece(Coord);
	void capturePiece(int, int);

	bool upgradePiece(Coord);
	bool upgradePiece(int, int);

	Piece* getPiece(Coord);
	Piece* getPiece(int, int);

	bool darkened(Coord);
	bool darkened(int, int);

	char getSprite(Coord);
	char getSprite(int, int);
private:
	Position* getPosition(Coord);
	Position* getPosition(int, int);
};

