#include "Strategy.h"

Strategy::Strategy(MovementController* controller)
{
	this->controller = controller;
	this->color = Piece::black;
}

Strategy::~Strategy()
{
}

string Strategy::toString() const
{
	return string();
}
