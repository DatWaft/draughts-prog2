#pragma once
#include "Strategy.h"
class Balanced: public Strategy
{
public:
	Balanced(MovementController*);
	string getMovement() const;
	Move getBest(List<Move>) const;
	Capture getBest(List<Capture>) const;
	string toString() const;
};

