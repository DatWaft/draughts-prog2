#include "Board.h"

Board::Board()
{
	board = new Position** [MAX];
	for (size_t i = 0; i < MAX; i++)
		board[i] = new Position* [MAX];

	for (size_t y = MAX; y > 0; y--)
		for (size_t x = 1; x <= MAX; x++)
			board[abs(int(y-MAX))][x-1] = new Position(x,y);

	// Algo así va a ser creado a nivel de coordenadas:
	// 8 [ | | | | | | | ]
	// 7 [ | | | | | | | ]
	// 6 [ | | | | | | | ]
	// 5 [ | | | | | | | ]
	// 4 [ | | | | | | | ]
	// 3 [ | | | | | | | ]
	// 2 [ | | | | | | | ]
	// 1 [ | | | | | | | ]
	//    1 2 3 4 5 6 7 8
}

Board::~Board()
{
	for (size_t i = 0; i < MAX; i++)
		for (size_t j = 0; j < MAX; j++)
			delete board[i][j];
	for (size_t i = 0; i < MAX; i++)
		delete[] board[i];
	delete[] board;
}

Coord Board::search(Piece* piece)
{
	for (size_t y = MAX; y > 0; y--)
		for (size_t x = 1; x <= MAX; x++)
			if (piece == this->getPiece(x, y))
				return { x,y };
}

void Board::setPiece(Coord coord, Piece* piece)
{
	board[abs(int(coord.y - MAX))][coord.x - 1]->setPiece(piece);
}

void Board::setPiece(size_t x, size_t y, Piece* piece)
{
	this->setPiece({ x,y }, piece);
}

void Board::capturePiece(Coord coord)
{
	if (getPiece(coord))
	{
		delete getPiece(coord);
		setPiece(coord, nullptr);
	}
}

void Board::capturePiece(size_t x, size_t y)
{
	capturePiece({ x,y });
}

Piece* Board::getPiece(Coord coord)
{
	return board[abs(int(coord.y - MAX))][coord.x - 1]->getPiece();
}

Piece* Board::getPiece(size_t x, size_t y)
{
	return this->getPiece({x,y});
}

bool Board::darkened(Coord coord)
{
	return board[abs(int(coord.y - MAX))][coord.x - 1]->darkened();
}

bool Board::darkened(size_t x, size_t y)
{
	return this->darkened({ x,y });
}

char Board::getSprite(Coord coord)
{
	if (getPiece(coord))
		return char(*getPiece(coord));
	return char(' ');
}

char Board::getSprite(size_t x, size_t y)
{
	return this->getSprite({x,y});
}
