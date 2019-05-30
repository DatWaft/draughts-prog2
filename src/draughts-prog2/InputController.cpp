#include "InputController.h"

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
		while (!(cin >> data))
		{
			cout << "Reingrese el dato" << endl;
			cin.clear();
			cin.ignore();
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
