#pragma once

#include <windows.h>
#include <iostream>
#include <sstream>

#define ESC "\x1b"
#define TAB "    "
using namespace std;

class ConsoleController
{
private:
	int width;
	int large;
	int bufferSize;
public:
	ConsoleController();
	virtual ~ConsoleController();
	void unicode();
	void virtualTerminal();
	void showTitle(string s);
	bool changeTheSize(int, int);
	void limitConsoleExpand();
	void limitConsoleSize();
	void disableQuickEditMode();

	


};

