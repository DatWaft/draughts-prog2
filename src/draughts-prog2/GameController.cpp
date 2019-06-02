#include "GameController.h"

GameControler::GameControler()
{
	viewControl = new ViewController();
	board = new Board();
}

GameControler::GameControler(Board* b)
{
	viewControl = new ViewController();
	board = b;
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

	for (int i = 8 ; i > 0; i--)
	{
		for (int j = 1; j < board->MAX+1; j++)
			game << board->getSprite(i, j) << ";";
		game << endl;
	}
	game.close();	
}

Board* GameControler::restoreTheGame(string gameSaved)
{
	ifstream game;
	string linea, aux;
	game.open("../" + gameSaved + ".txt");
	Board* b = new Board();

	//try {
	//	if (!game)			
	//	{
	//		throw Exception(" El archivo no existe");
	//	}
	//	if (game.peek() == std::ifstream::traits_type::eof())
	//		throw Exception(" El archivo esta vacio ");
	//}
	//catch (Exception error)
	//{
	//	viewControl->print(error.what());
	//}

	//int i = 8;
	//while (game.good())
	//{
	//	getline(game, linea, '\n');
	//	stringstream s(linea);
	//	if (!linea.empty())
	//	{
	//		int j = 1;
	//		while (getline(s, aux, ';'))
	//		{
	//			if (aux == " ")
	//				j += 1;
	//			else 
	//				if (aux == "X")
	//				{
	//					b->setPiece({ i,j }, new Men(Piece::white));  // Revisar la inversion que se hizo en x y o
	//					j += 1;
	//				}
	//				else
	//					if (aux == "O")
	//					{
	//						b->setPiece({ i,j }, new Men(Piece::black));
	//						j += 1;
	//					}
	//			
	//		
	//		}
	//		getline(s, aux, '\n');
	//	}
	//	i -= 1;
	//}
	//game.close();
	return b;
}
