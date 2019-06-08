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
	cout << "\nReingrese el dato " << endl;
	cin.clear();
	cin.ignore();
}

bool InputController::intValidation(int number)
{
	stringstream s(number);

	for (int i = 0; i < s.str().size(); i++)
		if (s.str()[i] < 49 || s.str()[i] > 64)
			return false;
	return true;
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
			cout << "  ";
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
		//while (!verifyMovementInput(data))
		//{
			fflush(stdin);
			cout << ESC"[u";
			//getline(cin, data);
			
		//}
	}
	return data;
}

int InputController::getInt()
{
	int data;
	cout << ESC"[s";
		while (!(cin >> data))
		{
			cout << ESC"[u";
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

int InputController::getASimpleInt()
{
	int data;
	cin >> data;
	return data;
}

bool InputController::verifyMovementInput(string move)
{
	int counter = 0;
	int spaceCounter = 0;
	
	if (move[0] == 32)
		return false;

	for (size_t i = 0; i < move.length(); i++)
	{
		if ((int(move[i])) < 56 )
		{
			if (int(move[i]) > 46 || int(move[i]) == 32)
			{
				counter += 1;
				spaceCounter += 1;
			}
			if (spaceCounter != 3 && move[i] == 32)
			{
				return false;
			}
			if (spaceCounter == 3 && move[i] != 32)
			{
				return false;
			}
			if (spaceCounter == 3)
			{
				spaceCounter = 0;
			}
			
		}		
	}
	if (counter == move.length())
		return true;
	else
		return false;
}
