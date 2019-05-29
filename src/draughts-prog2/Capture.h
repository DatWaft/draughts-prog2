#pragma once
#include "Move.h"
#include "List.h"
#include "Piece.h"

class Capture: public Move
{
private:
	Capture* precursor;
	List<Capture>* derivations;
	List<Piece*>* captures;
public:
	Capture(Coord, Coord);
	~Capture();

	void setPrecursor(Capture*);
	Capture* getPrecursor();

	void addCapture(Piece*);

	Capture createDerivation(Coord);
	Capture searchDerivation(string);

	List<Capture>* getDerivations();
	List<Piece*>* getCaptures();
};

