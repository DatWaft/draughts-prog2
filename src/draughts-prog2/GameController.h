#pragma once
#include "ViewController.h"
#include "InputController.h"
#include "MovementController.h"
#include <fstream>
#include <iostream>

class GameControler
{
private:
	ViewController* viewControl;
	InputController* inputControl;
	MovementController* movement;
	Board* board;
public:
	GameControler();
	~GameControler();
	bool runTheGame();
	void runTheGame(Board*);
	void saveTheGame(string);
	bool makeTheGame();
	void startBasicBoard();
	Board* getBoard();
	Board* restoreTheGame(string);


};


