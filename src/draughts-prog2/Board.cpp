#include "Board.h"

Board::Board()
{
	board = new Position** [MAX];
	for (int i = 0; i < MAX; i++)
		board[i] = new Position* [MAX];

	for (int i = MAX; i > 0; i--)
		for (int j = 1; j <= MAX; j++)
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
	for (int i = 0; i < MAX; i++)
		for (int j = 0; j < MAX; j++)
			delete board[i][j];
	for (int i = 0; i < MAX; i++)
		delete[] board[i];
	delete[] board;
}

Coord Board::search(Piece* piece)
{
	for (int i = MAX; i > 0; i--)
		for (int j = 1; j <= MAX; j++)
			if (piece == this->getPiece(i, j))
				return { i,j };
	return { 0,0 };
}

bool Board::movePiece(Coord source, Coord destination)
{
	if(!getPiece(source) || getPiece(destination))
		return false;
	setPiece(destination, getPiece(source));
	setPiece(source, nullptr);
	return true;

}

void Board::setPiece(Coord coord, Piece* piece)
{
	if (coord.i <= 0 || coord.j <= 0 || coord.i > MAX || coord.j > MAX)
		throw Exception("Coordenadas invalidas.");

	board[abs(int(coord.i - MAX))][coord.j - 1]->setPiece(piece);
}

void Board::setPiece(int i, int j, Piece* piece)
{
	this->setPiece({ i,j }, piece);
}

void Board::capturePieces(List<Coord> list)
{
	for (size_t i = 0; i < list.getSize(); i++)
		capturePiece(list[i]);
}

void Board::capturePiece(Coord coord)
{
	setPiece(coord, nullptr);
}

void Board::capturePiece(int i, int j)
{
	capturePiece({ i,j });
}

bool Board::upgradePiece(Coord coord)
{
	if(getPiece(coord) && !getPiece(coord)->isCrowned())
	{
		if (getPiece(coord)->isWhite() && coord.i == 8)
		{
			setPiece(coord, new King(Piece::white, coord));
			return true;
		}
		else if (getPiece(coord)->isBlack() && coord.i == 1)
		{
			setPiece(coord, new King(Piece::black, coord));
			return true;
		}
	}
	return false;
}

bool Board::upgradePiece(int i, int j)
{
	return upgradePiece({i,j});
}

Piece* Board::getPiece(Coord coord)
{
	if (coord.i <= 0 || coord.j <= 0 || coord.i > MAX || coord.j > MAX)
		throw Exception("Coordenadas invalidas.");
	return board[abs(int(coord.i - MAX))][coord.j - 1]->getPiece();
}

Piece* Board::getPiece(int i, int j)
{
	return this->getPiece({i,j});
}

bool Board::darkened(Coord coord)
{
	if (coord.i <= 0 || coord.j <= 0 || coord.i > MAX || coord.j > MAX)
		throw Exception("Coordenadas invalidas.");
	return board[abs(int(coord.i - MAX))][coord.j - 1]->darkened();
}

bool Board::darkened(int i, int j)
{
	return this->darkened({ i,j });
}

char Board::getSprite(Coord coord)
{
	if (getPiece(coord))
		return char(*getPiece(coord));
	return char(' ');
}

char Board::getSprite(int i, int j)
{
	return this->getSprite({i,j});
}

Position* Board::getPosition(Coord coord)
{
	return board[abs(int(coord.i - MAX))][coord.j - 1];
}

Position* Board::getPosition(int i, int j)
{
	return getPosition({i,j});
}
