#pragma once
#include "ConsoleController.h"
#include <iostream>
#include <sstream>

class InputController
{

public: 
	InputController();
	~InputController();

	void validation();
	string getString();
	int getInt(int = 0, int = 0);

};

