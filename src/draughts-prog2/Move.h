#pragma once
#include "Coord.h"

class Move
{
protected:
	Coord source;
	Coord destination;
public:
	Move(Coord, Coord);
	virtual ~Move();

	virtual Coord getSource() const;
	virtual Coord getDestination() const;
};

