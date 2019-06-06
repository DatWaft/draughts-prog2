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
	List<Capture> getCaptures(Piece::sprite);

	List<Move> getMovements(Piece*);
	List<Capture> getCaptures(Piece*);

	List<Move> getMovements(Men*);
	List<Move> getMovements(King*);

	List<Capture> getCaptures(Men*);
	List<Capture> getCaptures(King*);
};

