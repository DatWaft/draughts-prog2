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
	bool intValidation(int);

	string getString();
	string getMovementInput();

	int getInt();
	int getIntWhitLimits(int,int);
	int getASimpleInt();

	bool verifyMovementInput(string);

};



