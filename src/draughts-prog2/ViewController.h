#pragma once
#include "ConsoleController.h"
#include "Board.h"

#include <math.h>
#include <iostream>
#include <sstream>
#include "List.h"

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
	virtual ~ViewController();

	void displayBoard(Board*);
	void print(string, bool = true);
	void displayMainMenu();
	void displayMainInstructions();
	

	size_t amountOfStrings(string);
	size_t getHigherSize(string);

	string alingWidthAndLength(string);
	string centerString(string);
	
	template<class T>
	void showList(List<T>, string);
};

template<class T>
inline void ViewController::showList(List<T> v, string title)
{
	
	cout << title << ": ";
	for (size_t i = 0; i < v.getSize(); i++)
		cout << "[" << string(v[i]) << "]"; cout << endl;
	
}
