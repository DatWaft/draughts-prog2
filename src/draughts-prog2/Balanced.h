#pragma once
#include "Strategy.h"
class Balanced: public Strategy
{
	Balanced(MovementController*);
	string getMovement() const;
	Move getBest(List<Move>) const;
	Capture getBest(List<Capture>) const;
};

