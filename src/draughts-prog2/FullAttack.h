#pragma once
#include "Strategy.h"
class FullAttack: public Strategy
{
public:
	FullAttack(MovementController*);
	string getMovement() const;
	Move getBest(List<Move>) const;
	Capture getBest(List<Capture>) const;
	string toString() const;
};

