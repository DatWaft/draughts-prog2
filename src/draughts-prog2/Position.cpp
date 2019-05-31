#include "Position.h"

Position::Position(Coord coord): coord(coord) 
{
	this->piece = nullptr;
}

Position::Position(int i, int j)
{
	this->coord = { i,j };
	this->piece = nullptr;
}

Position::~Position()
{
	if (this->piece)
		delete this->piece;
	this->piece = nullptr;
}

Piece* Position::setPiece(Piece* piece)
{
	if (this->piece)
		delete this->piece;
	this->piece = piece;
	return piece;
}

Piece* Position::getPiece()
{
	return this->piece;
}

bool Position::darkened()
{
	if (coord.j % 2 == 0)
	{
		if (coord.i % 2 == 0)
			return false;
		else
			return true;
	}
	else
	{
		if (coord.i % 2 == 0)
			return true;
		else
			return false;
	}
}

Coord Position::getCoord()
{
	return coord;
}

int Position::getI()
{
	return coord.i;
}

int Position::getJ()
{
	return coord.j;
}
