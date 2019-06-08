#include "ViewController.h"



ViewController::ViewController()
{
	consoleControl = new ConsoleController();
}

ViewController::~ViewController()
{
	delete consoleControl;
}

void ViewController::displayBoard(Board* board)
{
	
	stringstream k;
	
	string aux; 
	k <<RED<< "*"<< string(27,'-')<<"*"<<NORMAL<<endl;
	for (int i = 8; i > 0; i--)
	{
		k <<RED<< "        | " <<NORMAL<< i;
		for (int j = 1; j < 9 ; j++)
			k << "[" << board->getSprite(i, j) << "]";
		k <<RED <<" |"<<NORMAL;
		k << endl;
	}
	k <<RED<<"        |"<<NORMAL<<"   1  2  3  4  5  6  7  8  "<<RED<<"|" <<NORMAL<< endl;
	k << RED << "*" << string(27, '-') << "*" << NORMAL<< endl;

	
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
	menuLine << CYAN << endl;
	menuLine << "1. Estrategia 1" << endl;
	menuLine << "2. Estrategia 2" << endl;
	menuLine << "3. Estrategia 3" << endl;
	menuLine << "4. Estrategia 4" << endl;
	menuLine << "5. Cargar juego" << endl;
	menuLine << "6. Crear juego" << endl;
	menuLine << "7. Salir" << endl;
	menuLine << NORMAL << endl;

	print(alingWidthAndLength(menuLine.str()));
	
}

void ViewController::displayMainInstructions()
{
	stringstream s2;
	s2 << CYAN;
	s2 << "    +" << string(106, '-') << "+" << endl;
	s2 << "| Instrucciones basicas para la aplicacion de movimientos y otras opciones:                                |" << endl;
	s2 << "| 1. Los movimientos validos solo tienen la forma: posicion actual (ij) espacio( ) posicion destino (ij)   |" << endl;
	s2 << "| 2. Para movimientos mas complicados como el de reyes y comer doble consultar la documentacion.           |" << endl;
	s2 << "| 3. Para guardar y salir, en vez de colocar el movimiento puede colocar la palabra 'Guardar'              |" << endl;
	s2 << "| 4. Para salir sin guardar, en vez de colocar el movimiento puede colocar la palabra 'Salir'              |" << endl;
	s2 << "| 5. Para cambiar manualmente la estrategia del IA puede coloar la palabra 'Cambiar'                       |" << endl;
	s2 << "   +" << string(106, '-') << "+";
	s2 << NORMAL;

	print(centerString(s2.str()));
}

size_t ViewController::amountOfStrings(string s)
{
	stringstream x(s);
	string aux;
	size_t contador = 0;
	while (getline(x,aux))
	{
		contador += 1;
	};
	return contador;
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

	size_t margenx = (((120 - getHigherSize(x.str())) / 2));
	size_t margeny = ((30 - amountOfStrings(x.str())) / 2);

	r << ESC"[" << margeny << "B";

	while (getline(x, aux))
	{
		r << string(margenx, ' ') + aux << endl;
	}
	
	return r.str();
}

void ViewController::print(string text, bool jump)
{
	if (jump)
	{
		cout << text << endl;
	}
	else
		cout << text + " ";
	
}


