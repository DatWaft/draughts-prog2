#pragma once
#include "ViewController.h"
#include "InputController.h"
#include "MovementController.h"
#include "Random.h"
#include "Balanced.h"
#include "FullAttack.h"
#include "FullDefense.h"
#include "Strategy.h"
#include <fstream>
#include <iostream>


class GameControler
{
private:
	ViewController* viewControl;
	InputController* inputControl;
	MovementController* movement;
	Board* board;
	Strategy* strategy;

public:
	GameControler();
	~GameControler();
	bool runTheGame();
	void runTheGame(Board*,bool = false);
	void saveTheGame(string);
	bool makeTheGame();
	bool emptyBoard();
	void startBasicBoard();
	Board* getBoard();
	Board* restoreTheGame(string,string*);
	bool winner(string&);
	void checkAndUpgrade();
};


