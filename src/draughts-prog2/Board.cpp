#include "Board.h"

Board::Board()
{
	board = new Position** [MAX];
	for (size_t i = 0; i < MAX; i++)
		board[i] = new Position* [MAX];

	for (size_t i = MAX; i > 0; i--)
		for (size_t j = 1; j <= MAX; j++)
			board[abs(int(i-MAX))][j-1] = new Position(i,j);

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
	for (size_t i = MAX; i > 0; i--)
		for (size_t j = 1; j <= MAX; j++)
			if (piece == this->getPiece(i, j))
				return { i,j };
	return { 0,0 };
}

void Board::setPiece(Coord coord, Piece* piece)
{
	if (coord.i <= 0 || coord.j <= 0 || coord.i > MAX || coord.j > MAX)
		throw Exception("Coordenadas invalidas.");

	board[abs(int(coord.i - MAX))][coord.j - 1]->setPiece(piece);
}

void Board::setPiece(size_t i, size_t j, Piece* piece)
{
	this->setPiece({ i,j }, piece);
}

void Board::capturePiece(Coord coord)
{
	setPiece(coord, nullptr);
}

void Board::capturePiece(size_t i, size_t j)
{
	capturePiece({ i,j });
}

bool Board::upgradePiece(Coord coord)
{
	if(getPiece(coord) && !getPiece(coord)->isCrowned())
	{
		if (getPiece(coord)->isWhite() && coord.i == 8)
		{
			setPiece(coord, new King(Piece::white));
			return true;
		}
		else if (getPiece(coord)->isBlack() && coord.i == 1)
		{
			setPiece(coord, new King(Piece::black));
			return true;
		}
	}
	return false;
}

bool Board::upgradePiece(size_t i, size_t j)
{
	return upgradePiece({i,j});
}

Piece* Board::getPiece(Coord coord)
{
	if (coord.i <= 0 || coord.j <= 0 || coord.i > MAX || coord.j > MAX)
		throw Exception("Coordenadas invalidas.");
	return board[abs(int(coord.i - MAX))][coord.j - 1]->getPiece();
}

Piece* Board::getPiece(size_t i, size_t j)
{
	return this->getPiece({i,j});
}

bool Board::darkened(Coord coord)
{
	if (coord.i <= 0 || coord.j <= 0 || coord.i > MAX || coord.j > MAX)
		throw Exception("Coordenadas invalidas.");
	return board[abs(int(coord.i - MAX))][coord.j - 1]->darkened();
}

bool Board::darkened(size_t i, size_t j)
{
	return this->darkened({ i,j });
}

char Board::getSprite(Coord coord)
{
	if (getPiece(coord))
		return char(*getPiece(coord));
	return char(' ');
}

char Board::getSprite(size_t i, size_t j)
{
	return this->getSprite({i,j});
}
