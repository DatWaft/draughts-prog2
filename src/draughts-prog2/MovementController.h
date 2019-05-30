#pragma once
#include "Board.h"
#include "Capture.h"

class MovementController
{
private:
	Board* board;
public:
	MovementController(Board*);
	~MovementController();
};

