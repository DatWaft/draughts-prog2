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
	bool operator == (const Capture&);
	~Capture();

	Coord getEnd() const;

	Capture* getPrecursor();
	Capture* getSubsequent();
	Capture* createSubsequent(Coord);
	Capture* createSubsequent(Capture);

	List<Coord> getCaptures();
	int getNumberCaptures();

	operator bool() const;
	operator string() const;
	friend ostream& operator << (ostream&, const Capture&);
};

