#include "GameController.h"

GameControler::GameControler()
{
	viewControl = new ViewController();
}

GameControler::~GameControler()
{
	delete viewControl;
}
