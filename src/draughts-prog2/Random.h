#pragma once
#include <time.h>
#include "Strategy.h"


class Random: public Strategy
{
public:
	Random(MovementController*);
	string getMovement() const;
	string toString() const;
};

