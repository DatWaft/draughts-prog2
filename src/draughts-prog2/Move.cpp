#include "Move.h"

Move::Move(Coord source, Coord destination)
{
	this->source = source;
	this->destination = destination;
}

Move::~Move()
{
}

Coord Move::getSource() const
{
	return this->source;
}

Coord Move::getDestination() const
{
	return this->destination;
}
