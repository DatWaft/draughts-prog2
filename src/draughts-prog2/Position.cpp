#include "Position.h"

Position::Position(Coord coord): coord(coord) 
{
	this->piece = nullptr;
}

Position::Position(size_t x, size_t y)
{
	this->coord = { x,y };
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
	if (coord.x % 2 == 0)
	{
		if (coord.y % 2 == 0)
			return false;
		else
			return true;
	}
	else
	{
		if (coord.y % 2 == 0)
			return true;
		else
			return false;
	}
}

Coord Position::getCoord()
{
	return coord;
}

size_t Position::getX()
{
	return coord.x;
}

size_t Position::getY()
{
	return coord.y;
}
