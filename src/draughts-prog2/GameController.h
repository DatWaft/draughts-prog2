#pragma once
#include "ViewController.h"
#include "InputController.h"
#include <fstream>
#include <iostream>

class GameControler
{
private:
	ViewController* viewControl;
	InputController* inputControl;
	Board* board;
public:
	GameControler();
	
	~GameControler();
	bool runTheGame();
	void runTheGame(Board*);
	void saveTheGame(string);
	bool makeTheGame();
	void makeBasicBoard();
	Board* getBoard();
	Board* restoreTheGame(string);


};


