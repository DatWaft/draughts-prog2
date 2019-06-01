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
	cout << "Reingrese el dato" << endl;
	cin.clear();
	cin.ignore();
}


string InputController::getString()
{
	string data;
		while (!(getline(cin,data)))
		{
			validation();
		}
		return data;
}

string InputController::getMovementInput()
{

	string data;
	getline(cin, data);
		while(!verifyMovementInput(data))
		{	
			fflush(stdin);
			getline(cin, data);
		}
	
	return data;
}

int InputController::getInt(int a, int b)
{
	int data;

	if (a && b == 0)
		while (!(cin >> data))
		{
			validation();
		}
	else
		while (!(cin >> data || data > a || data < b))
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
