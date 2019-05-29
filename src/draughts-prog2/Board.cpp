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
	return { 0,0 };
}

void Board::setPiece(Coord coord, Piece* piece)
{
	if (coord.x <= 0 || coord.y <= 0 || coord.x > MAX || coord.y > MAX)
		throw Exception("Coordenadas invalidas.");

	board[abs(int(coord.y - MAX))][coord.x - 1]->setPiece(piece);
}

void Board::setPiece(size_t x, size_t y, Piece* piece)
{
	this->setPiece({ x,y }, piece);
}

void Board::capturePiece(Coord coord)
{
	setPiece(coord, nullptr);
}

void Board::capturePiece(size_t x, size_t y)
{
	capturePiece({ x,y });
}

bool Board::upgradePiece(Coord coord)
{
	if(getPiece(coord) && !getPiece(coord)->isCrowned())
	{
		if (getPiece(coord)->isWhite() && coord.y == 8)
		{
			setPiece(coord, new King(Piece::white));
			return true;
		}
		else if (getPiece(coord)->isBlack() && coord.y == 1)
		{
			setPiece(coord, new King(Piece::black));
			return true;
		}
	}
	return false;
}

bool Board::upgradePiece(size_t x, size_t y)
{
	return upgradePiece({x,y});
}

Piece* Board::getPiece(Coord coord)
{
	if (coord.x <= 0 || coord.y <= 0 || coord.x > MAX || coord.y > MAX)
		throw Exception("Coordenadas invalidas.");
	return board[abs(int(coord.y - MAX))][coord.x - 1]->getPiece();
}

Piece* Board::getPiece(size_t x, size_t y)
{
	return this->getPiece({x,y});
}

bool Board::darkened(Coord coord)
{
	if (coord.x <= 0 || coord.y <= 0 || coord.x > MAX || coord.y > MAX)
		throw Exception("Coordenadas invalidas.");
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
