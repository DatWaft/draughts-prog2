#pragma once
#include "Board.h"
#include "Capture.h"
#include "Men.h"
#include "King.h"

class MovementController
{
private:
	Board* board;
public:
	MovementController(Board*);
	~MovementController();
	List<Move> getMovimientos(Men*);
	List<Move> getMovimientos(King*);
	List<Capture> getCaptures(Men*);
	List<Capture> getCaptures(King*);
};

