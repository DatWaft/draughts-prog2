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
