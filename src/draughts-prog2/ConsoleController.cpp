#include "ConsoleController.h"
#include <Windows.h>

ConsoleController::ConsoleController()
{
	virtualTerminal();
	unicode();
	changeTheSize(120, 30);
	limitConsoleExpand();
	limitConsoleSize();
	disableQuickEditMode();
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

bool ConsoleController::changeTheSize(int newWidth, int newLong)
{
	
		_COORD coord; // Crea un objeto tipo COORD que guarda coordenadas, "windows.h".
		coord.X = newWidth; // Al atributo X de coord se le asigna newAncho.
		coord.Y = newLong; // Al atributo Y de coord se le asigna newLargo.
		// Lo siguiente declara el largo y ancho de la consola
		_SMALL_RECT Rect; // Crea un objetivo tipo SMALL RECT que contiene las dimensiones de la consola.
		Rect.Top = 0;				// Al atributo Top de coord se le asigna 0.
		Rect.Left = 0;				// Al atributo Left de coord se le asigna 0.
		Rect.Bottom = newLong - 1;	// Al atributo Bottom de coord se le asigna newLargo -1.
		Rect.Right = newWidth - 1;	// Al atributo Right de coord se le asigna newAncho -1.	

		HANDLE Handle = GetStdHandle(STD_OUTPUT_HANDLE); // Obtiene la consola que va a ser manipulada
		if (Handle == NULL) // Si la Handle es un valor erroneo devuelve false.
		{
			return false;
		}

		if (!SetConsoleScreenBufferSize(Handle, coord)) // El metodo cambia el tamaño del buffer (el scroll lateral al lado derecho de la consola).
		{
			return false;
		}

		if (!SetConsoleWindowInfo(Handle, true, &Rect)) // Cambia la informacion de la ventana.
		{
			return false;
		}
		width = newWidth;
		large = newLong;
		bufferSize = newLong;
		return true;
	
}

void ConsoleController::limitConsoleExpand()
{
	HWND consoleWindow = GetConsoleWindow();
	SetWindowLong(consoleWindow, GWL_STYLE, GetWindowLong(consoleWindow, GWL_STYLE) & ~WS_MAXIMIZEBOX);
}

void ConsoleController::limitConsoleSize()
{
	HWND consoleWindow = GetConsoleWindow();
	SetWindowLong(consoleWindow, GWL_STYLE, GetWindowLong(consoleWindow, GWL_STYLE) & ~WS_SIZEBOX);
}

void ConsoleController::disableQuickEditMode()
{
	DWORD prev_mode;
	HANDLE handle = GetStdHandle(STD_INPUT_HANDLE);
	GetConsoleMode(handle, &prev_mode);
	SetConsoleMode(handle, prev_mode & ~ENABLE_QUICK_EDIT_MODE);
}


