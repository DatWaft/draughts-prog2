#pragma once
#include <string>
#include "Coord.h"

using std::string;
using std::to_string;

class Move
{
protected:
	Coord source;
	Coord destination;
public:
	Move();
	Move(Coord, Coord);
	virtual ~Move();
	Move(const Move&);
	void operator = (const Move&);
	bool operator == (const Move&);

	virtual Coord getSource() const;
	virtual Coord getDestination() const;

	virtual operator bool() const;
	virtual operator string() const;
};

