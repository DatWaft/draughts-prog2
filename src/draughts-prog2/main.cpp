#include <iostream>
#include <string>
#include <sstream>

using namespace std;

#include "MovementController.h"
#include "ViewController.h"
#include "GameController.h"
#include "InputController.h"


int main()
{
	GameControler* g = new GameControler();

	g->runTheGame();
	
	system("pause");
}