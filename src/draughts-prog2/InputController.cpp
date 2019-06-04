#include "InputController.h"
#include <string>


InputController::InputController()
{
}

InputController::~InputController()
{
}

void InputController::validation()
{
	cout << "Reingrese el dato " << endl;
	cin.clear();
	cin.ignore();
}


string InputController::getString()
{
	string data = "";
	cout << ESC"[s";
	getline(cin, data);
	while (data.empty())
	{
		cout << string(120, ' ') << ESC"[u";
			fflush(stdin);
			cout << ESC"[u";
			getline(cin, data);
	}
	return data;
}

string InputController::getMovementInput()
{

	string data = "";
	cout << ESC"[s";
	while (data.empty())
	{
		cout << string(120, ' ') << ESC"[u";
		getline(cin, data);
		while (!verifyMovementInput(data))
		{
			
			fflush(stdin);
			
			cout << ESC"[u";
			getline(cin, data);
		}
	}
	return data;
}

int InputController::getInt()
{
	int data;

		while (!(cin >> data))
		{
			validation();
		}

	return data;
}

int InputController::getIntWhitLimits(int a, int b)
{
	int data;

	while ((!(cin >> data) || data < a || data > b))
	{
		validation();

	}
	return data;
}

bool InputController::verifyMovementInput(string move)
{
	int counter = 0;
	;

	for (size_t i = 0; i < move.length(); i++)
	{
		if ((int(move[i])) < 56 /* && counter == 0 || move[i] == ' ' && counter % 2 != 0*/)
		{
			if (int(move[i]) > 46 || int(move[i]) == 32)
			counter += 1;		
		}		
	}
	if (counter == move.length())
		return true;
	else
		return false;
}
