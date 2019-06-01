#include "MovementController.h"

MovementController::MovementController(Board* board)
{
	this->board = board;
}

MovementController::~MovementController()
{
}

bool MovementController::move(string str, Piece::sprite color)
{
	Move move = str_to_move(str);
	if(bool(move))
		return this->move(move, color);
	return false;
}

Move MovementController::str_to_move(string str)
{
	if (str.length() < 5)
		return Move();
	return Move({ stoi(string(1,str[0])), stoi(string(1,str[1])) }, { stoi(string(1,str[3])), stoi(string(1,str[4])) });
}

bool MovementController::move(Move move, Piece::sprite color)
{
	auto moves = getMovements(color);
	if (moves.inside(move))
	{
		board->movePiece(move.getSource(), move.getDestination());
		return true;
	}
	return false;
}

List<Move> MovementController::getMovements()
{
	auto moves = getMovements(Piece::black);
	moves.append(getMovements(Piece::white));
	return moves;
}

List<Move> MovementController::getMovements(Piece::sprite color)
{
	List<Move> moves;
	for (int i = Board::MAX; i > 0; i--)
		for (int j = 1; j <= Board::MAX; j++)
			if (board->getPiece(i, j) && board->getPiece(i, j)->getColor() == color)
				moves.append(getMovements(board->getPiece(i, j)));
	return moves;
}

List<Move> MovementController::getMovements(Piece* piece)
{
	if (Men* new_piece = dynamic_cast<Men*>(piece))
		return getMovements(new_piece);
	return List<Move>();
}

List<Move> MovementController::getMovements(Men* piece)
{
	List<Move> moves;
	// Modificadores:
	const Coord UP = { -1,0 };
	const Coord DOWN = { 1,0 };
	const Coord LEFT = { 0,-1 };
	const Coord RIGHT = { 0,1 };
	// --------------
	Coord position = piece->getPosition();

	// [-| |-] // X: posición de la pieza
	// [ |X| ] // +: posiciones a checkear si la pieza es blanca.
	// [+| |+] // -: posiciones a checkear si la pieza es negra.

	if (piece->isBlack())
	{
		Coord to_check = position + UP;
		if (bool(position + LEFT)) // Si la posición es válida.
		{
			to_check += LEFT;
			if (!board->getPiece(to_check)) // Si la posición está libre.
				moves.insert(Move(piece->getPosition(), to_check));
		}
		to_check = position + UP;
		if (bool(position + RIGHT)) // Si la posición es válida.
		{
			to_check += RIGHT;
			if (!board->getPiece(to_check)) // Si la posición está libre.
				moves.insert(Move(piece->getPosition(), to_check));
		}
	}
	else
	{
		Coord to_check = position + DOWN;
		if (bool(position + LEFT)) // Si la posición es válida.
		{
			to_check += LEFT;
			if (!board->getPiece(to_check)) // Si la posición está libre.
				moves.insert(Move(piece->getPosition(), to_check));
		}
		to_check = position + DOWN;
		if (bool(position + RIGHT)) // Si la posición es válida.
		{
			to_check += RIGHT;
			if (!board->getPiece(to_check)) // Si la posición está libre.
				moves.insert(Move(piece->getPosition(), to_check));
		}
	}
	return moves;
}