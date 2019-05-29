#include "ConsoleController.h"

ConsoleController::ConsoleController()
{
}

ConsoleController::~ConsoleController()
{
}

void ConsoleController::unicode()
{
	setlocale(LC_ALL, "spanish");
	SetConsoleCP(1252);
	SetConsoleOutputCP(1252);
}

void ConsoleController::virtualTerminal()
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD dwMode = 0;
	GetConsoleMode(hOut, &dwMode);
	SetConsoleMode(hOut, dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING);
}

void ConsoleController::showTitle(string s)
{
	cout << ESC"[47;30m";
	cout << s << string(120 - s.length(), ' ');
	cout << ESC"[0m";
}

