#pragma once
#include "Move.h"
#include "List.h"
#include "Position.h"

class Capture: public Move
{
private:
	Capture* precursor;
	List<Capture> derivations;
	List<Position*> captures;
public:
	Capture();
	Capture(Coord, Coord, Capture* = nullptr);
	Capture(Coord, Coord, List<Capture>, List<Position*>, Capture* = nullptr);
	Capture(const Capture&);
	void operator = (const Capture&);
	~Capture();

	Capture* getPrecursor();
	List<Capture> getDerivations();
	void setDerivations(List<Capture>);
	List<Position*> getCaptures();
	void setCaptures(List<Position*>);
};

