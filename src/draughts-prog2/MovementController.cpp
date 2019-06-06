#include "MovementController.h"

MovementController::MovementController(Board* board)
{
	this->board = board;
}

MovementController::~MovementController()
{
}

bool MovementController::move(string str, Piece::sprite color)
{
	Move move = str_to_move(str);
	if(bool(move))
		return this->move(move, color);
	return false;
}

Move MovementController::str_to_move(string str)
{
	if (str.length() < 5)
		return Move();
	try
	{
		return Move({ stoi(string(1,str[0])), stoi(string(1,str[1])) }, { stoi(string(1,str[3])), stoi(string(1,str[4])) });
	}
	catch (...)
	{
		return Move();
	}
}

bool MovementController::move(Move move, Piece::sprite color)
{
	auto moves = getMovements(color);
	if (moves.inside(move))
	{
		board->movePiece(move.getSource(), move.getDestination());
		return true;
	}
	return false;
}

List<Move> MovementController::getMovements(Piece::sprite color)
{
	List<Move> moves;
	for (int i = Board::MAX; i > 0; i--)
		for (int j = 1; j <= Board::MAX; j++)
			if (board->getPiece(i, j) && board->getPiece(i, j)->getColor() == color)
				moves.append(getMovements(board->getPiece(i, j)));
	return moves;
}

List<Capture> MovementController::getCaptures(Piece::sprite color)
{
	List<Capture> moves;
	for (int i = Board::MAX; i > 0; i--)
		for (int j = 1; j <= Board::MAX; j++)
			if (board->getPiece(i, j) && board->getPiece(i, j)->getColor() == color)
				moves.append(getCaptures(board->getPiece(i, j)));
	return moves;
}

List<Move> MovementController::getMovements(Piece* piece)
{
	if (Men * new_piece = dynamic_cast<Men*>(piece))
		return getMovements(new_piece);
	else if (King * new_piece = dynamic_cast<King*>(piece))
		return getMovements(new_piece);

	return List<Move>();
}

List<Capture> MovementController::getCaptures(Piece* piece)
{
	if (Men * new_piece = dynamic_cast<Men*>(piece))
		return getCaptures(new_piece);
	else if (King * new_piece = dynamic_cast<King*>(piece))
		return getCaptures(new_piece);

	return List<Capture>();
}

List<Move> MovementController::getMovements(Men* piece)
{
	List<Move> moves;
	// Modificadores:
	const Coord UP = { 1,0 };
	const Coord DOWN = { -1,0 };
	const Coord LEFT = { 0,-1 };
	const Coord RIGHT = { 0,1 };
	// --------------
	Coord position = piece->getPosition();

	// [+| |+] // X: posición de la pieza
	// [ |X| ] // +: posiciones a checkear si la pieza es blanca.
	// [-| |-] // -: posiciones a checkear si la pieza es negra.

	if (piece->isWhite())
	{
		Coord to_check = position + UP;
		if (bool(position + LEFT)) // Si la posición es válida.
		{
			to_check += LEFT;
			if (!board->getPiece(to_check)) // Si la posición está libre.
				moves.insert(Move(piece->getPosition(), to_check));
		}
		to_check = position + UP;
		if (bool(position + RIGHT)) // Si la posición es válida.
		{
			to_check += RIGHT;
			if (!board->getPiece(to_check)) // Si la posición está libre.
				moves.insert(Move(piece->getPosition(), to_check));
		}
	}
	else
	{
		Coord to_check = position + DOWN;
		if (bool(position + LEFT)) // Si la posición es válida.
		{
			to_check += LEFT;
			if (!board->getPiece(to_check)) // Si la posición está libre.
				moves.insert(Move(piece->getPosition(), to_check));
		}
		to_check = position + DOWN;
		if (bool(position + RIGHT)) // Si la posición es válida.
		{
			to_check += RIGHT;
			if (!board->getPiece(to_check)) // Si la posición está libre.
				moves.insert(Move(piece->getPosition(), to_check));
		}
	}
	return moves;
}

List<Move> MovementController::getMovements(King* piece)
{
	List<Move> moves;
	// Modificadores:
	const Coord UP = { 1,0 };
	const Coord DOWN = { -1,0 };
	const Coord LEFT = { 0,-1 };
	const Coord RIGHT = { 0,1 };
	// --------------
	Coord position = piece->getPosition();
	Coord to_check;

	// [1| |2] 1,2,3,4 = Posiciones a checkear hasta tocar fondo o alguna pieza.
	// [ |X| ] X = Pieza actual
	// [3| |4]

	to_check = position + UP + LEFT;
	while (bool(to_check) && !board->getPiece(to_check))
	{
		moves.insert(Move(position, to_check));
		to_check = to_check + UP + LEFT;
	}

	to_check = position + UP + RIGHT;
	while (bool(to_check) && !board->getPiece(to_check))
	{
		moves.insert(Move(position, to_check));
		to_check = to_check + UP + RIGHT;
	}

	to_check = position + DOWN + LEFT;
	while (bool(to_check) && !board->getPiece(to_check))
	{
		moves.insert(Move(position, to_check));
		to_check = to_check + DOWN + LEFT;
	}

	to_check = position + DOWN + RIGHT;
	while (bool(to_check) && !board->getPiece(to_check))
	{
		moves.insert(Move(position, to_check));
		to_check = to_check + DOWN + RIGHT;
	}

	return moves;
}

List<Capture> MovementController::getCaptures(Men* piece)
{
	List<Capture> moves;
	// Modificadores:
	const Coord UP = { 1,0 };
	const Coord DOWN = { -1,0 };
	const Coord LEFT = { 0,-1 };
	const Coord RIGHT = { 0,1 };
	// --------------
	Coord position = piece->getPosition();
	Coord to_check;

	// [o| | | | ] // O: posición donde quedaría la pieza.
	// [ |+| | | ] // X: posición de la pieza
	// [ | |X| | ] // +: posición a checkear para ver enemigo.
	// [ | | | | ]
	// [ | | | | ]
	if (piece->isWhite())
	{
		to_check = position + UP + LEFT;
		if (bool(to_check) && board->getPiece(to_check) && board->getPiece(to_check)->isBlack()) // Si la pieza existe y es negra.
		{
			to_check = to_check + UP + LEFT;
			if (bool(to_check) && !board->getPiece(to_check)) // Si la posición a moverse esta disponible y vacía.
			{
				Capture aux(position, to_check);
				moves.insert(aux);

				Men* temp = new Men(piece->getColor(), to_check);
				auto list = getCaptures(temp);
				delete temp;

				for (size_t i = 0; i < list.getSize(); i++)
				{
					aux = Capture(position, to_check);
					aux.createSubsequent(list[i]);
					moves.insert(aux);
				}
			}
		}
	}
	
	// [ | | | |o] // O: posición donde quedaría la pieza.
	// [ | | |+| ] // X: posición de la pieza
	// [ | |X| | ] // +: posición a checkear para ver enemigo.
	// [ | | | | ]
	// [ | | | | ]
	if (piece->isWhite())
	{
		to_check = position + UP + RIGHT;
		if (bool(to_check) && board->getPiece(to_check) && board->getPiece(to_check)->isBlack()) // Si la pieza existe y es negra.
		{
			to_check = to_check + UP + RIGHT;
			if (bool(to_check) && !board->getPiece(to_check)) // Si la posición a moverse esta disponible y vacía.
			{
				Capture aux(position, to_check);
				moves.insert(aux);

				Men* temp = new Men(piece->getColor(), to_check);
				auto list = getCaptures(temp);
				delete temp;

				for (size_t i = 0; i < list.getSize(); i++)
				{
					aux = Capture(position, to_check);
					aux.createSubsequent(list[i]);
					moves.insert(aux);
				}
			}
		}
	}

	// [ | | | | ] // O: posición donde quedaría la pieza.
	// [ | | | | ] // X: posición de la pieza
	// [ | |X| | ] // +: posición a checkear para ver enemigo.
	// [ |+| | | ]
	// [o| | | | ]
	if (piece->isBlack())
	{
		to_check = position + DOWN + LEFT;
		if (bool(to_check) && board->getPiece(to_check) && board->getPiece(to_check)->isWhite()) // Si la pieza existe y es negra.
		{
			to_check = to_check + DOWN + LEFT;
			if (bool(to_check) && !board->getPiece(to_check)) // Si la posición a moverse esta disponible y vacía.
			{
				Capture aux(position, to_check);
				moves.insert(aux);

				Men* temp = new Men(piece->getColor(), to_check);
				auto list = getCaptures(temp);
				delete temp;

				for (size_t i = 0; i < list.getSize(); i++)
				{
					aux = Capture(position, to_check);
					aux.createSubsequent(list[i]);
					moves.insert(aux);
				}
			}
		}
	}

	// [ | | | | ] // O: posición donde quedaría la pieza.
	// [ | | | | ] // X: posición de la pieza
	// [ | |X| | ] // +: posición a checkear para ver enemigo.
	// [ | | |+| ]
	// [ | | | |o]
	if (piece->isBlack())
	{
		to_check = position + DOWN + RIGHT;
		if (bool(to_check) && board->getPiece(to_check) && board->getPiece(to_check)->isWhite()) // Si la pieza existe y es negra.
		{
			to_check = to_check + DOWN + RIGHT;
			if (bool(to_check) && !board->getPiece(to_check)) // Si la posición a moverse esta disponible y vacía.
			{
				Capture aux(position, to_check);
				moves.insert(aux);

				Men* temp = new Men(piece->getColor(), to_check);
				auto list = getCaptures(temp);
				delete temp;

				for (size_t i = 0; i < list.getSize(); i++)
				{
					aux = Capture(position, to_check);
					aux.createSubsequent(list[i]);
					moves.insert(aux);
				}
			}
		}
	}

	return moves;
}

List<Capture> MovementController::getCaptures(King* piece)
{
	return List<Capture>();
}

