#include "Piece.h"

Piece::Piece(sprite color, Coord coord): color(color), position(coord) { }

Piece::~Piece() { }

bool Piece::isBlack() const
{
	return this->color == sprite::black;
}

bool Piece::isWhite() const
{
	return !this->isBlack();
}

void Piece::setPosition(Coord coord)
{
	position = coord;
}

Piece::sprite Piece::getColor() const
{
	return this->color;
}

Coord Piece::getPosition() const
{
	return position;
}

Piece::operator string() const
{
	return string(1, char(*this));
}

string Piece::render() const
{
	return string(*this);
}
