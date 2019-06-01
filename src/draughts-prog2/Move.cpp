#include "Move.h"

Move::Move()
{
	this->source = { 0,0 };
	this->destination = { 0,0 };
}

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

Move::operator bool() const
{
	return bool(source) && bool(destination);
}

Move::operator string() const
{
	return to_string(source.i) + to_string(source.j) + " " + to_string(destination.i) + to_string(destination.j);
}
