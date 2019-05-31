#pragma once
#include "Move.h"
#include "List.h"
#include "Position.h"

class Capture: public Move
{
private:
	Capture* precursor;
	Capture* subsequent;
private:
	Capture(Coord, Coord, Capture*);
public:
	Capture();
	Capture(Coord, Coord);
	Capture(const Capture&);
	void operator = (const Capture&);
	~Capture();

	Capture* getPrecursor();
	Capture* getSubsequent();
	Capture* createSubsequent(Coord);

	operator string();
};

