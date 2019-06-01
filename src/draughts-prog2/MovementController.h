#pragma once
#include "Board.h"
#include "Capture.h"
#include "Men.h"
#include "King.h"

using std::stoi;

class MovementController
{
private:
	Board* board;
public:
	MovementController(Board*);
	~MovementController();
	bool move(string, Piece::sprite);
	Move str_to_move(string);
	bool move(Move, Piece::sprite);
	List<Move> getMovements(Piece::sprite);
	List<Move> getMovements(Piece*);
	List<Move> getMovements(Men*);
};

