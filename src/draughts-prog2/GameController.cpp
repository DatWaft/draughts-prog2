#include "GameController.h"

GameControler::GameControler()
{
	this->viewControl = new ViewController();
	this->inputControl = new InputController();
	this->board = nullptr;

	


}


GameControler::~GameControler()
{
	delete this->viewControl;
}

bool GameControler::runTheGame()
{
	int option;
	while (true)
	{
		system("cls");

		viewControl->displayMainMenu();
		viewControl->print("Inserte la opcion de juego que desea realizar", false);
		option = inputControl->getInt();
		switch (option)
		{

		case 1:
			viewControl->print("gg");
			system("pause");
			break;
		case 2:
			break;
			case 3:break;
			case 4:break;
			case 5: //cargar
			{
				system("cls");
				viewControl->print(viewControl->alingWidthAndLength("Inserte el nombre de la partida guardada, el nombre debe ser exactamente el mismo: "));
				viewControl->print(string((120/2), ' '),false);
				this->board = restoreTheGame(inputControl->getString());
				runTheGame(board);
				system("pause");
				break;
			}
			case 6:
			{
				makeTheGame();
				break;

			}
			case 7: false;
				return false;
			default:
				viewControl->print("Reingrese el dato.", false);
				break;


			}
	}

}

void GameControler::runTheGame(Board*)
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

bool GameControler::makeTheGame()
{

	board = new Board();
	int position;
	int x; 
	int y;
	while (true)
	{
		system("cls");
		viewControl->displayBoard(this->board);
		viewControl->print("\n");
		stringstream s;
		s << "Ingrese el tipo de ficha que desea insertar: "<<endl;
		s <<"1. para piezas black ""O""" << endl;
		s <<"2. para piezas White ""X""" << endl;
		s <<"3. para terminar" << endl;
		viewControl->print(viewControl->centerString(s.str()));
		viewControl->print(string(120 / 2, ' '),false);
		switch (inputControl->getIntWhitLimits(1,2))
		{
		case 1:
		{
			viewControl->print("");
			viewControl->print(viewControl->centerString("Inserte el numero equivalente a la posicion en la que desea ingresar la ficha: Ejemplo 50 == {5,0}"), false);
			viewControl->print(string(120 / 2, ' '), false);
			position = inputControl->getIntWhitLimits(11, 88);
			y = position % 10;
			position = position / 10;
			x = position;
			board->setPiece({ x,y }, new Men(Piece::black));
			break;
		}
		case 2:
		{
			viewControl->print("");
			viewControl->print(viewControl->centerString("Inserte el numero equivalente a la posicion en la que desea ingresar la ficha: Ejemplo 50 == {5,0}"), false);
			viewControl->print(string(120 / 2, ' '), false);
			position = inputControl->getIntWhitLimits(11, 88);
			y = position % 10;
			position = position / 10;
			x = position;
			board->setPiece({ x,y }, new Men(Piece::white));
			break;
		}
		case 3:
			return false;
		default:
			viewControl->print("Ha ingresado una opcion incorrecta, reingrese porfavor ");
			break;
		}

	}
	return true;
}

Board* GameControler::restoreTheGame(string gameSaved)
{
	ifstream game;
	string linea, aux;
	game.open("../" + gameSaved + ".txt");
	Board* b = new Board();

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

	int i = 8;
	while (game.good())
	{
		getline(game, linea, '\n');
		stringstream s(linea);
		if (!linea.empty())
		{
			int j = 1;
			while (getline(s, aux, ';'))
			{
				if (aux == " ")
					j += 1;
				else 
					if (aux == "X")
					{
						b->setPiece({ i,j }, new Men(Piece::white));  // Revisar la inversion que se hizo en x y o
						j += 1;
					}
					else
						if (aux == "O")
						{
							b->setPiece({ i,j }, new Men(Piece::black));
							j += 1;
						}
			}
			getline(s, aux, '\n');
		}
		i -= 1;
	}
	game.close();
	return b;
}
