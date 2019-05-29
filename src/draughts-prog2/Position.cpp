#include "Position.h"

ostream& operator<<(ostream& out, const Coord& coord)
{
	out << "[" << coord.i << "," << coord.j << "]";
	return out;
}

Position::Position(Coord coord): coord(coord) 
{
	this->piece = nullptr;
}

Position::Position(size_t i, size_t j)
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

void Position::setPiece(Piece* piece)
{
	if (this->piece)
		delete this->piece;
	this->piece = piece;
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

size_t Position::getI()
{
	return coord.i;
}

size_t Position::getJ()
{
	return coord.j;
}
