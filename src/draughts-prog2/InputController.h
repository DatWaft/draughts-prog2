#pragma once
#include "ConsoleController.h"
#include <iostream>
#include <sstream>

class InputController
{

public: 
	InputController();
	virtual ~InputController();

	void validation();

	string getString();
	string getMovementInput();

	int getInt(int = 0, int = 0);

	bool verifyMovementInput(string);

};



