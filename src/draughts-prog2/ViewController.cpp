#include "ViewController.h"



ViewController::ViewController()
{
	consoleControl = new ConsoleController();
}

ViewController::~ViewController()
{
	delete consoleControl;
}

void ViewController::positionBoard(string boardString)
{
	stringstream x(boardString);
	stringstream k;

	string aux, aux2;
	k << "*"<< string(27,'-')<<"*"<<endl;
	for (size_t i = 0; i < 8; i++)
	{
		getline(x, aux, '\n');
		k << "| "<< i<< aux <<" |"<< endl;
	}
	k <<"|   1  2  3  4  5  6  7  8  |" << endl;
	k << "*" << string(27, '-') << "*" << endl;

	
	print(centerString(k.str()));
}

string ViewController::centerString(string s)
{
	stringstream x(s);
	stringstream k;
	string aux;
	size_t margen;
	while (getline(x, aux))
	{
		margen = (((120 - aux.size()) / 2));
		if (aux.length() % 2 != 0)
		{
			margen += 1;
		}
		
		k << string(margen, ' ') + aux << endl;
		
	}
	return k.str();
}

void ViewController::displayMainMenu()
{
	stringstream menuLine;
	
	string aux;
	menuLine << "1. Opcion 1234" << endl;
	menuLine << "2. Opcion 2" << endl;
	menuLine << "3. Opcion 3" << endl;
	menuLine << "4. Opcion 4" << endl;

	print(alingWidthAndLength(menuLine.str()));
	
}

size_t ViewController::getHigherSize(string textLine)
{
	stringstream x(textLine);
	string aux;
	size_t higher = 0;
	while (getline(x, aux))
	{
		if (aux.length() > higher)
			higher = aux.length();
	}
	return higher;
}

string ViewController::alingWidthAndLength(string textToAline)
{
	stringstream x(textToAline);
	stringstream r;
	string aux;
	size_t margen = (((120 - getHigherSize(x.str())) / 2));

	while (getline(x, aux))
	{
		r << string(margen, ' ') + aux << endl;
	}
	// falta alinear largo

	return r.str();
}

void ViewController::print(string text)
{
	cout << text << endl;
}


