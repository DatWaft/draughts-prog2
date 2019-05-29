#pragma once

#include <windows.h>
#include <iostream>
#include <sstream>

#define ESC "\x1b"
#define TAB "    "
using namespace std;

class ConsoleController
{
public:
	ConsoleController();
	~ConsoleController();
	void unicode();
	void virtualTerminal();
	void showTitle(string s);
	


};

