#include "GameController.h"

GameControler::GameControler()
{
	viewControl = new ViewController();
	board = new Board();
}

GameControler::~GameControler()
{
	delete viewControl;
}

void GameControler::runTheGame()
{
}

void GameControler::saveTheGame(string name)
{
	ofstream game;
	game.open("../" + name + ".txt");

	for (int i = 0; i < board->MAX; i++)
	{
		for (int j = 0; j < board->MAX; j++)
			game << board->getSprite(i + 1, j + 1) << ";";
		game << endl;
	}
	game.close();	
}

Board* GameControler::restoreTheGame(string)
{
	ifstream game;
	string linea, aux;
	

	try {
		if (!game)			
		{
			throw Exception(" El archivo no existe");
		}
		if (game.peek() == std::ifstream::traits_type::eof())
			throw Exception(" El archivo esta vacio ");
	}
	catch (Exception error)
	{
		viewControl->print(error.what());
	}

	while (game.good())
	{
		getline(game, linea, '\n');
		stringstream s(linea);
		
		if (!linea.empty())
		{
			while(getline(s,aux,';'))
				if (aux !=  " ")
				{
					// Rellenar creacion de piezas, 
				}
		}
	}

}
