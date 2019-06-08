#pragma once
#include "Strategy.h"
class FullDefense: public Strategy
{
public:
	FullDefense(MovementController*);
	string getMovement() const;
	Move getBest(List<Move>) const;
	Capture getBest(List<Capture>) const;
	string toString() const;
};

