#include "Piece.h"

Piece::Piece(sprite color): color(color) { }

Piece::~Piece() { }

bool Piece::black() const
{
	return this->color == sprite::black;
}

bool Piece::white() const
{
	return !this->black();
}

Piece::operator string() const
{
	return string(1, char(*this));
}

string Piece::render() const
{
	return string(*this);
}
