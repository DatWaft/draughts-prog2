#pragma once
#include "ViewController.h"
#include <fstream>
#include <iostream>

class GameControler
{
private:
	ViewController* viewControl;
	Board* board;
public:
	GameControler();
	~GameControler();
	void runTheGame();
	void saveTheGame(string);
	Board* restoreTheGame(string);


};


