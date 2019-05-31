#include "MovementController.h"

MovementController::MovementController(Board* board)
{
	this->board = board;
}

MovementController::~MovementController()
{
}

List<Move> MovementController::getMovimientos(Men* piece)
{
	List<Move> v;
	// MODIFICADORES:
	const Coord UP = { -1, 0 };
	const Coord DOWN = { 1, 0 };
	const Coord LEFT = { 0, -1 };
	const Coord RIGHT = { 0, 1 };
	// --------------
	if (piece->isBlack()) // Si es una ficha no coronada negra, sus movimientos todos son hacia abajo.
	{

	}
	else	// Si es una ficha no coronada blanca, sus movimientos todos son hacia arriba.
	{

	}

	return List<Move>();
}

List<Move> MovementController::getMovimientos(King* piece)
{
	return List<Move>();
}

List<Capture> MovementController::getCaptures(Men* piece)
{
	return List<Capture>();
}

List<Capture> MovementController::getCaptures(King* piece)
{
	return List<Capture>();
}
