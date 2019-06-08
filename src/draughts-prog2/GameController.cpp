#include "GameController.h"
#include <conio.h>

GameControler::GameControler()
{
	this->viewControl = new ViewController();
	this->inputControl = new InputController();
	this->board = nullptr;
	this->movement = nullptr;
	strategy = nullptr;
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
		bool verifyOption = false;
		
		while (!verifyOption)
		{
			verifyOption = false;
			viewControl->displayMainMenu();
			viewControl->print(YELLOW, false);
			viewControl->print(string(35, ' ') + "Inserte la opcion de juego que desea realizar", false);
			viewControl->print(NORMAL, false);
			option = inputControl->getInt();
			if (inputControl->intValidation(option))
				verifyOption = true;
		}

		switch (option)
		{

		case 1:
		{	startBasicBoard();
		if (strategy)
		{
			delete strategy;
		}
		this->movement = new MovementController(board);
		strategy = new Random(movement);
		runTheGame(board);

		
		break;
		}
		case 2:
		{
			startBasicBoard();
			if (strategy)
			{
				delete strategy;
			}
			startBasicBoard();
			this->movement = new MovementController(board);
			strategy = new Balanced(movement);
			runTheGame(board);
			system("pause");
			break;
		}
			case 3:
			{
				startBasicBoard();
				if (strategy)
				{
					delete strategy;
				}
				startBasicBoard();
				this->movement = new MovementController(board);
				strategy = new FullAttack(movement);
				runTheGame(board);
				
				break;
			}
			case 4:
			{
				startBasicBoard();
				if (strategy)
				{
					delete strategy;
				}
				startBasicBoard();
				this->movement = new MovementController(board);
				strategy = new FullDefense(movement);
				runTheGame(board);
				
				break;
			}
			case 5: //cargar
			{
				string nameOfGame;
				string restoreStrategy;
				system("cls");
				viewControl->print(viewControl->alingWidthAndLength("Inserte el nombre de la partida guardada, el nombre debe ser exactamente el mismo: "));
				viewControl->print(string((120/2), ' '),false);
				nameOfGame = inputControl->getString();
				this->board = restoreTheGame(nameOfGame, &restoreStrategy);
				if (!emptyBoard())
				{
					this->movement = new MovementController(board);
					if (restoreStrategy == "random")
						strategy = new Random(movement);
					else
						if (restoreStrategy == "balanced")
							strategy = new Balanced(movement);
						else
							if (restoreStrategy == "fullAtaque")
								strategy = new FullAttack(movement);
							else
								if (restoreStrategy == "fullDefense")
									strategy = new FullDefense(movement);
					runTheGame(board,true);
				
					break;
				}
				else
				{
					system("cls");
					viewControl->print(YELLOW, false);
					viewControl->print(viewControl->alingWidthAndLength("El juego no existe, presione una tecla para volver al menu principal."),false);
					viewControl->print(NORMAL, false);
					_getch();
					break;
				}
			}
			case 6:
			{
				makeTheGame();
				this->movement = new MovementController(board);
				strategy = new Random(movement);
				runTheGame(board);
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

void GameControler::runTheGame(Board*, bool charge)
{
	bool flag = true;
	bool moveFlag = true;
	bool moveFalse = true;
	string move = " ";
	string iaMove;
	string win;
	/*int opcion;*/

	int start = 0;
	bool playerMove = true;
	
	if (charge == false)
	{
		system("cls");
		viewControl->print(GREEN,false);
		viewControl->print(viewControl->alingWidthAndLength("Digite 1 para que la IA realice el primer movimiento, 2 para que el usuario inicie la partida:"), false);
		viewControl->print(NORMAL, false);
		viewControl->print(string(35, ' '), false);
		start = inputControl->getIntWhitLimits(1, 2);
	}
	else
		start = 2;

	
	while (flag)
	{
		if (!winner(win))
		{
			flag = false;
			break;
		}
		system("cls");
		if (playerMove && start == 1)
		{
			iaMove = strategy->getMovement();
			movement->move(iaMove, Piece::black);
		}
	
		
		checkAndUpgrade();
		viewControl->print(RED,false);
		viewControl->print("Estrategia actual: "+strategy->toString(),false);
		viewControl->print(NORMAL);
		viewControl->displayMainInstructions();
		viewControl->displayBoard(board);
		viewControl->print(GREEN, false);
		if (movement->getCaptures(Piece::white).empty())
		{
			viewControl->showList<Move>(movement->getMovements(Piece::white), "w");
		}
		else
			viewControl->showList<Capture>(movement->purgeCaptures(movement->getCaptures(Piece::white)), "w");

		viewControl->print(NORMAL, false);
		viewControl->print(" ");

		if (!moveFalse)
		{
			viewControl->print(RED, false);
			viewControl->print("El ultimo movimiento no era correcto o no era permitido, no se realizó. ");
			viewControl->print(NORMAL);
			moveFalse = true;
		}

		viewControl->print(YELLOW, false);
		viewControl->print(viewControl->centerString("  El ultimo movimiento de la maquina fue: " + iaMove +(string(44- iaMove.size(), ' ') )),false);
		viewControl->print(NORMAL, false);
		viewControl->print(" ");
		viewControl->print(YELLOW, false);
		viewControl->print(string(23, ' ')+"Escriba el movimiento que desea realizar:",false);
		viewControl->print(NORMAL, false);
	
		
		move = inputControl->getMovementInput();
		
		if (move == "Salir" || move == "SALIR" || move == "salir")
		{
			viewControl->print(YELLOW);
			viewControl->print("\n\nPresione una tecla para volver al menu principal.");
			viewControl->print(NORMAL);
			flag = false;
		}
		else if (move == "Guardar" || move == "guardar" || move == "GUARDAR")
		{
			string name;
			system("cls");
			viewControl->print("\n\n\n");
			viewControl->print(GREEN);
			viewControl->print(viewControl->centerString("Ingrese el nombre del juego.  "));
			viewControl->print(viewControl->centerString("advertencia, si el nombre pertenece a otro juego ya almacenado, este se sobreescribira."));
			viewControl->print(NORMAL);
			name = inputControl->getString();
			saveTheGame(name);
			
			flag = false;
		}
		else
			if (move == "Cambiar" || move == "cambiar" || move == "CAMBIAR")
			{
				system("cls");
				/*stringstream change;*/
				int strategyOption;
				viewControl->print("\n\n");
				viewControl->print(GREEN);
				viewControl->print(viewControl->centerString(("Elija el tipo de estreategia por la que desea cambiar:      ")),false);
				viewControl->print(viewControl->centerString("1. Estraetgia aleatoria." + string(36, ' ')),false);
				viewControl->print(viewControl->centerString("2. Estrategia equilibrada."+string(34, ' ')),false);
				viewControl->print(viewControl->centerString("3. Estrategia de ataque." +string(36, ' ')),false);
				viewControl->print(viewControl->centerString("4. Estrategia de defensa."+string(36, ' ')),false);
				viewControl->print(NORMAL);
				strategyOption = inputControl->getIntWhitLimits(1, 4);
				Strategy* temp = strategy;
				if (strategyOption == 1)
					strategy = new Random(movement);
				else
					if (strategyOption == 2)
						strategy = new Balanced(movement);
					else
						if (strategyOption == 3)
							strategy = new FullAttack(movement);
						else
							if (strategyOption == 4)
								strategy = new FullDefense(movement);
				delete temp;
				
			}
			else
				if (start == 1)
				{
					if (movement->move(move, Piece::white))
						playerMove = true;
					else
					{
						playerMove = false;
						moveFalse = false;
					}
				}
				else
					if (start == 2)
					{
						if (movement->move(move, Piece::white))
						{
							iaMove = strategy->getMovement();
							movement->move(iaMove, Piece::black);
						}
					}
	
		if (!winner(win))
			flag = false;
	}

	system("cls");
	if (!win.empty())
	{
		viewControl->print(CYAN, false);
		viewControl->print(viewControl->alingWidthAndLength(("El ganador ha sido: " + win)), false);
		viewControl->print(NORMAL, false);
		system("pause");
	}
	
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
	game << strategy->toString() << endl;
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
		s << "Ingrese el tipo de ficha que desea insertar: (Una ver seleccionado 'terminar', El juego iniciara.) "<<endl;
		s << "1. para piezas black O" << string(77,' ')<< endl;
		s << "2. para piezas White X" << string(77,' ')<< endl;
		s << "3. para piezas reina White W"<< string(71, ' ') << endl;
		s << "4. para piezas reina Black X" << string(71, ' ') << endl;
		s << "5. para terminar" << string(83, ' ') << endl;
		viewControl->print(viewControl->centerString(s.str()));
		viewControl->print(string(120 / 2, ' '),false);
		switch (inputControl->getIntWhitLimits(1,5))
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
				cout << position;
				y = position % 10;
				position = position / 10;
				x = position;
				board->setPiece({ x,y }, new Men(Piece::white));
			break;
		}
		case 3:
			viewControl->print("");
			viewControl->print(viewControl->centerString("Inserte el numero equivalente a la posicion en la que desea ingresar la ficha: Ejemplo 50 == {5,0}"), false);
			viewControl->print(string(120 / 2, ' '), false);
			position = inputControl->getIntWhitLimits(11, 88);
			y = position % 10;
			position = position / 10;
			x = position;
			board->setPiece({ x,y }, new King(Piece::white));
			break;
		case 4:
			viewControl->print("");
			viewControl->print(viewControl->centerString("Inserte el numero equivalente a la posicion en la que desea ingresar la ficha: Ejemplo 50 == {5,0}"), false);
			viewControl->print(string(120 / 2, ' '), false);
			position = inputControl->getIntWhitLimits(11, 88);
			y = position % 10;
			position = position / 10;
			x = position;
			board->setPiece({ x,y }, new King(Piece::black));
			break;
		case 5:
			return false;
		default:
			viewControl->print("Ha ingresado una opcion incorrecta, reingrese porfavor ");
			break;
		}

	}
	return true;
}

bool GameControler::emptyBoard()
{

	for (int i = 8; i > 0; i--)
		for (int j = 1; j < 9; j++)
			if (board->getSprite(i,j) == 'X' || board->getSprite(i, j) == 'O' || board->getSprite(i,j)== 'B' || board->getSprite(i, j) == 'N')
				return false;
				
	return true;
}

void GameControler::startBasicBoard()
{
	this->board = new Board();

	for (int i = 8; i >= 6; i--)
		for (int j = 1; j <= board->MAX; j++)
			if (board->darkened({ i,j }))
				board->setPiece({ i,j }, new Men(Piece::black));
	for (int i = 3; i >= 1; i--)
		for (int j = 1; j <= board->MAX; j++)
			if (board->darkened({ i,j }))
				board->setPiece({ i,j }, new Men(Piece::white));

}

Board* GameControler::getBoard()
{
	return board;
}

Board* GameControler::restoreTheGame(string gameSaved,string* strategyName)
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
						else
							if (aux == "N")
							{
								b->setPiece({ i,j }, new King(Piece::black));
								j += 1;
							}
							else
								if (aux == "B")
								{
									b->setPiece({ i,j }, new King(Piece::white));
									j += 1;
								}
			}
			getline(s, aux, '\n');
			if (i == 0)
			{
				getline(s, aux, '\n');
				*strategyName = aux;
			}
		}
		i -= 1;
		
	}
	
	game.close();
	return b;
}

bool GameControler::winner(string& winner)
{
	if (movement->getCaptures(Piece::white).empty() && movement->getMovements(Piece::white).empty())
	{
		winner = "Black";
		return false;
		
	}
	else
		if (movement->getCaptures(Piece::black).empty() && movement->getMovements(Piece::black).empty())
		{
			winner = "White";
			return false;
			
		}
		
	return true;
}

void GameControler::checkAndUpgrade()
{
	for (int j = 1; j <= Board::MAX; j++)
	{
		board->upgradePiece({ 8,j });
		board->upgradePiece({ 1,j });
	}
}