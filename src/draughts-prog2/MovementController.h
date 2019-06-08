#pragma once
#include <sstream>
#include "Board.h"
#include "Capture.h"
#include "Men.h"
#include "King.h"
#include "Weight.h"

using std::stoi;
using std::stringstream;

class MovementController
{
private:
	Board* board;
public:
	MovementController(Board*);
	~MovementController();
	bool move(string, Piece::sprite);

	Move str_to_move(string);
	Capture str_to_capture(string);
	bool move(Move, Piece::sprite);
	bool move(Capture, Piece::sprite);

	List<Capture> purgeCaptures(List<Capture>);
	int kingsEaten(List<Coord>);

	List<Move> getMovements(Piece::sprite);
	List<Capture> getCaptures(Piece::sprite);

	List<Move> getMovements(Piece*);
	List<Capture> getCaptures(Piece*);

	List<Move> getMovements(Men*);
	List<Move> getMovements(King*);

	List<Capture> getCaptures(Men*);
	List<Capture> getCaptures(King*);

	List<Weight> weightMovements(List<Move>);
	List<Weight> weightMovements(List<Capture>);
	Weight reconPosition(Coord, Piece*);
};

