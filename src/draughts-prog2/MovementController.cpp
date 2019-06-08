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
	Move* move = str_to_move(str);
	if (!move)
		return false;
	if (bool(*move))
	{
		if (Capture* capture = dynamic_cast<Capture*>(move))
		{
			bool buffer = this->move(*capture, color);
			delete move;
			return buffer;
		}
		else
		{
			bool buffer = this->move(*move, color);
			delete move;
			return buffer;
		}
	}
	delete move;
	return false;
}

Move* MovementController::str_to_move(string str)
{
	if (str.length() < 5)
		return nullptr;

	stringstream s(str);
	string aux;

	Coord source;
	Coord destination;

	if (!getline(s, aux, ' ') || aux.length() != 2)
		return nullptr;

	try
	{
		source = { stoi(string(1,aux[0])),stoi(string(1,aux[1])) };
	}
	catch (...)
	{
		return nullptr;
	}

	if (!getline(s, aux, ' ') || aux.length() != 2)
		return nullptr;

	try
	{
		destination = { stoi(string(1,aux[0])),stoi(string(1,aux[1])) };
	}
	catch (...)
	{
		return nullptr;
	}

	// Aqu� se decide si el movimiento es simple o comer:
	if (abs(source.i - destination.i) == 1 && abs(source.j - destination.j) == 1)
		return new Move(source, destination);
	else
	{
		Capture* move = new Capture(source, destination);
		Capture* pointer = move;

		while (getline(s, aux, ' '))
		{
			if (aux.length() != 2)
			{
				delete move;
				return nullptr;
			}
			try
			{
				pointer = pointer->createSubsequent({ stoi(string(1,aux[0])),stoi(string(1,aux[1])) });
			}
			catch (...)
			{
				delete move;
				return nullptr;
			}
		}

		std::cout << std::endl << string(*move) << std::endl;
		return move;
	}
}

bool MovementController::move(Move move, Piece::sprite color)
{
	auto to_check = getCaptures(color);
	if (to_check.getSize() > 0)
		return false;

	auto moves = getMovements(color);
	if (moves.inside(move))
	{
		board->movePiece(move.getSource(), move.getDestination());
		return true;
	}
	return false;
}

bool MovementController::move(Capture move, Piece::sprite color)
{
	auto moves = purgeCaptures(getCaptures(color));
	if (moves.inside(move))
	{
		board->movePiece(move.getSource(), move.getEnd());
		board->capturePieces(move.getCaptures());
		return true;
	}
	return false;
}

List<Capture> MovementController::purgeCaptures(List<Capture> list)
{
	if (list.empty())
		return list;

	List<Capture> maxs;
	int max = list[0].getNumberCaptures();
	maxs.insert(list[0]);


	for (size_t i = 1; i < list.getSize(); i++)
	{
		if (list[i].getNumberCaptures() == max)
		{
			if (this->kingsEaten(maxs[0].getCaptures()) < this->kingsEaten(list[i].getCaptures()))
			{
				maxs.clear();
				maxs.insert(list[i]);
			}
			else if (this->kingsEaten(maxs[0].getCaptures()) == this->kingsEaten(list[i].getCaptures()))
			{
				maxs.insert(list[i]);
			}
		}
		else if (list[i].getNumberCaptures() > max)
		{
			max = list[i].getNumberCaptures();
			maxs.clear();
			maxs.insert(list[i]);
		}
	}

	return maxs;
}

int MovementController::kingsEaten(List<Coord> list)
{
	int cont = 0;
	for (size_t i = 0; i < list.getSize(); i++)
		if (bool(list[i]) && board->getPiece(list[i]) && board->getPiece(list[i])->isCrowned())
			cont++;
	return cont;
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

	// [+| |+] // X: posici�n de la pieza
	// [ |X| ] // +: posiciones a checkear si la pieza es blanca.
	// [-| |-] // -: posiciones a checkear si la pieza es negra.

	if (piece->isWhite())
	{
		Coord to_check = position + UP;
		if (bool(position + LEFT)) // Si la posici�n es v�lida.
		{
			to_check += LEFT;
			if (!board->getPiece(to_check)) // Si la posici�n est� libre.
				moves.insert(Move(piece->getPosition(), to_check));
		}
		to_check = position + UP;
		if (bool(position + RIGHT)) // Si la posici�n es v�lida.
		{
			to_check += RIGHT;
			if (!board->getPiece(to_check)) // Si la posici�n est� libre.
				moves.insert(Move(piece->getPosition(), to_check));
		}
	}
	else
	{
		Coord to_check = position + DOWN;
		if (bool(position + LEFT)) // Si la posici�n es v�lida.
		{
			to_check += LEFT;
			if (!board->getPiece(to_check)) // Si la posici�n est� libre.
				moves.insert(Move(piece->getPosition(), to_check));
		}
		to_check = position + DOWN;
		if (bool(position + RIGHT)) // Si la posici�n es v�lida.
		{
			to_check += RIGHT;
			if (!board->getPiece(to_check)) // Si la posici�n est� libre.
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

	// [o| | | | ] // O: posici�n donde quedar�a la pieza.
	// [ |+| | | ] // X: posici�n de la pieza
	// [ | |X| | ] // +: posici�n a checkear para ver enemigo.
	// [ | | | | ]
	// [ | | | | ]
	if (piece->isWhite())
	{
		to_check = position + UP + LEFT;
		if (bool(to_check) && board->getPiece(to_check) && board->getPiece(to_check)->isBlack()) // Si la pieza existe y es negra.
		{
			to_check = to_check + UP + LEFT;
			if (bool(to_check) && !board->getPiece(to_check)) // Si la posici�n a moverse esta disponible y vac�a.
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
	
	// [ | | | |o] // O: posici�n donde quedar�a la pieza.
	// [ | | |+| ] // X: posici�n de la pieza
	// [ | |X| | ] // +: posici�n a checkear para ver enemigo.
	// [ | | | | ]
	// [ | | | | ]
	if (piece->isWhite())
	{
		to_check = position + UP + RIGHT;
		if (bool(to_check) && board->getPiece(to_check) && board->getPiece(to_check)->isBlack()) // Si la pieza existe y es negra.
		{
			to_check = to_check + UP + RIGHT;
			if (bool(to_check) && !board->getPiece(to_check)) // Si la posici�n a moverse esta disponible y vac�a.
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

	// [ | | | | ] // O: posici�n donde quedar�a la pieza.
	// [ | | | | ] // X: posici�n de la pieza
	// [ | |X| | ] // +: posici�n a checkear para ver enemigo.
	// [ |+| | | ]
	// [o| | | | ]
	if (piece->isBlack())
	{
		to_check = position + DOWN + LEFT;
		if (bool(to_check) && board->getPiece(to_check) && board->getPiece(to_check)->isWhite()) // Si la pieza existe y es negra.
		{
			to_check = to_check + DOWN + LEFT;
			if (bool(to_check) && !board->getPiece(to_check)) // Si la posici�n a moverse esta disponible y vac�a.
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

	// [ | | | | ] // O: posici�n donde quedar�a la pieza.
	// [ | | | | ] // X: posici�n de la pieza
	// [ | |X| | ] // +: posici�n a checkear para ver enemigo.
	// [ | | |+| ]
	// [ | | | |o]
	if (piece->isBlack())
	{
		to_check = position + DOWN + RIGHT;
		if (bool(to_check) && board->getPiece(to_check) && board->getPiece(to_check)->isWhite()) // Si la pieza existe y es negra.
		{
			to_check = to_check + DOWN + RIGHT;
			if (bool(to_check) && !board->getPiece(to_check)) // Si la posici�n a moverse esta disponible y vac�a.
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
	List<Capture> moves;
	// Modificadores:
	const Coord UP = { 1,0 };
	const Coord DOWN = { -1,0 };
	const Coord LEFT = { 0,-1 };
	const Coord RIGHT = { 0,1 };
	// --------------
	Coord position = piece->getPosition();
	Coord to_check;

	// [o| | | | ] // O: posici�n donde quedar�a la pieza.
	// [ |+| | | ] // X: posici�n de la pieza
	// [ | |X| | ] // +: posici�n a checkear para ver enemigo.
	// [ | | | | ] // Nota: La distancia entre X y + puede ser tan amplia como se desee.
	// [ | | | | ]
	to_check = position + UP + LEFT;
	while (bool(to_check) && !board->getPiece(to_check))
		to_check = to_check + UP + LEFT;
	if (bool(to_check) && board->getPiece(to_check) && ((board->getPiece(to_check)->isBlack() && piece->isWhite()) || board->getPiece(to_check)->isWhite() && piece->isBlack()))
	{
		to_check = to_check + UP + LEFT;
		if (bool(to_check) && !board->getPiece(to_check)) // Si la posici�n a moverse esta disponible y vac�a.
		{
			Capture aux(position, to_check);
			moves.insert(aux);

			King* temp = new King(piece->getColor(), to_check);
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

	// [ | | | |o] // O: posici�n donde quedar�a la pieza.
	// [ | | |+| ] // X: posici�n de la pieza
	// [ | |X| | ] // +: posici�n a checkear para ver enemigo.
	// [ | | | | ] // Nota: La distancia entre X y + puede ser tan amplia como se desee.
	// [ | | | | ]
	to_check = position + UP + RIGHT;
	while (bool(to_check) && !board->getPiece(to_check))
		to_check = to_check + UP + RIGHT;
	if (bool(to_check) && board->getPiece(to_check) && ((board->getPiece(to_check)->isBlack() && piece->isWhite()) || board->getPiece(to_check)->isWhite() && piece->isBlack()))
	{
		to_check = to_check + UP + RIGHT;
		if (bool(to_check) && !board->getPiece(to_check)) // Si la posici�n a moverse esta disponible y vac�a.
		{
			Capture aux(position, to_check);
			moves.insert(aux);

			King* temp = new King(piece->getColor(), to_check);
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

	// [ | | | | ] // O: posici�n donde quedar�a la pieza.
	// [ | | | | ] // X: posici�n de la pieza
	// [ | |X| | ] // +: posici�n a checkear para ver enemigo.
	// [ |+| | | ] // Nota: La distancia entre X y + puede ser tan amplia como se desee.
	// [o| | | | ]
	to_check = position + DOWN + LEFT;
	while (bool(to_check) && !board->getPiece(to_check))
		to_check = to_check + DOWN + LEFT;
	if (bool(to_check) && board->getPiece(to_check) && ((board->getPiece(to_check)->isBlack() && piece->isWhite()) || board->getPiece(to_check)->isWhite() && piece->isBlack()))
	{
		to_check = to_check + DOWN + LEFT;
		if (bool(to_check) && !board->getPiece(to_check)) // Si la posici�n a moverse esta disponible y vac�a.
		{
			Capture aux(position, to_check);
			moves.insert(aux);

			King* temp = new King(piece->getColor(), to_check);
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

	// [ | | | | ] // O: posici�n donde quedar�a la pieza.
	// [ | | | | ] // X: posici�n de la pieza
	// [ | |X| | ] // +: posici�n a checkear para ver enemigo.
	// [ | | |+| ] // Nota: La distancia entre X y + puede ser tan amplia como se desee.
	// [ | | | |o]
	to_check = position + DOWN + RIGHT;
	while (bool(to_check) && !board->getPiece(to_check))
		to_check = to_check + DOWN + RIGHT;
	if (bool(to_check) && board->getPiece(to_check) && ((board->getPiece(to_check)->isBlack() && piece->isWhite()) || board->getPiece(to_check)->isWhite() && piece->isBlack()))
	{
		to_check = to_check + DOWN + RIGHT;
		if (bool(to_check) && !board->getPiece(to_check)) // Si la posici�n a moverse esta disponible y vac�a.
		{
			Capture aux(position, to_check);
			moves.insert(aux);

			King* temp = new King(piece->getColor(), to_check);
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

	return moves;
}

