#include "Piece.h"

Piece::Piece(sprite color): color(color) { }

Piece::~Piece() { }

bool Piece::isBlack() const
{
	return this->color == sprite::black;
}

bool Piece::isWhite() const
{
	return !this->isBlack();
}

Piece::operator string() const
{
	return string(1, char(*this));
}

string Piece::render() const
{
	return string(*this);
}
