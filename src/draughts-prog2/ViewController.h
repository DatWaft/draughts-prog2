#pragma once
#include "ConsoleController.h"
#include "Board.h"

#include <math.h>
#include <iostream>
#include <sstream>

#define YELLOW ESC"[93m"
#define RED ESC"[91m"
#define GREEN ESC"[92m"
#define CYAN ESC"[96m"
#define NORMAL ESC"[0m"

using namespace std;

class ViewController
{
private:
	ConsoleController* consoleControl;
public:
	ViewController();
	~ViewController();

	void displayBoard(Board*);
	void print(string);
	void displayMainMenu();

	size_t amountOfStrings(string);
	size_t getHigherSize(string);

	string alingWidthAndLength(string);
	string centerString(string);
	
	

};

