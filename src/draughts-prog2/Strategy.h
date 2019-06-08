#pragma once
#include "MovementController.h"


class Strategy
{
protected:
	MovementController* controller;
	Piece::sprite color;
public:
	Strategy(MovementController*);
	virtual ~Strategy();

	virtual string getMovement() const = 0;
};

