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
	Move move_m = str_to_move(str);
	Capture move_c = str_to_capture(str);
	if (!move_m)
		return false;
	if (bool(move_m))
	{
		if (move(move_m, color))
			return true;
		return move(move_c, color);
	}
	return false;
}

Move MovementController::str_to_move(string str)
{
	if (str.length() < 5)
		return Move();

	stringstream s(str);
	string aux;

	Coord source;
	Coord destination;

	if (!getline(s, aux, ' ') || aux.length() != 2)
		return Move();

	try
	{
		source = { stoi(string(1,aux[0])),stoi(string(1,aux[1])) };
	}
	catch (...)
	{
		return Move();
	}

	if (!getline(s, aux, ' ') || aux.length() != 2)
		return Move();

	try
	{
		destination = { stoi(string(1,aux[0])),stoi(string(1,aux[1])) };
	}
	catch (...)
	{
		return Move();
	}

	return Move(source, destination);
}

Capture MovementController::str_to_capture(string str)
{
	if (str.length() < 5)
		return Capture();

	stringstream s(str);
	string aux;

	Coord source;
	Coord destination;

	if (!getline(s, aux, ' ') || aux.length() != 2)
		return Capture();

	try
	{
		source = { stoi(string(1,aux[0])),stoi(string(1,aux[1])) };
	}
	catch (...)
	{
		return Capture();
	}

	if (!getline(s, aux, ' ') || aux.length() != 2)
		return Capture();

	try
	{
		destination = { stoi(string(1,aux[0])),stoi(string(1,aux[1])) };
	}
	catch (...)
	{
		return Capture();
	}

	Capture move = Capture(source, destination);
	Capture* pointer = &move;

	while (getline(s, aux, ' '))
	{
		if (aux.length() != 2)
		{
			return Capture();
		}
		try
		{
			pointer = pointer->createSubsequent({ stoi(string(1,aux[0])),stoi(string(1,aux[1])) });
		}
		catch (...)
		{
			return Capture();
		}
	}

	return move;
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
	// [ | | | | ] // Nota: La distancia entre X y + puede ser tan amplia como se desee.
	// [ | | | | ]
	to_check = position + UP + LEFT;
	while (bool(to_check) && !board->getPiece(to_check))
		to_check = to_check + UP + LEFT;
	if (bool(to_check) && board->getPiece(to_check) && ((board->getPiece(to_check)->isBlack() && piece->isWhite()) || board->getPiece(to_check)->isWhite() && piece->isBlack()))
	{
		to_check = to_check + UP + LEFT;
		if (bool(to_check) && !board->getPiece(to_check)) // Si la posición a moverse esta disponible y vacía.
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

	// [ | | | |o] // O: posición donde quedaría la pieza.
	// [ | | |+| ] // X: posición de la pieza
	// [ | |X| | ] // +: posición a checkear para ver enemigo.
	// [ | | | | ] // Nota: La distancia entre X y + puede ser tan amplia como se desee.
	// [ | | | | ]
	to_check = position + UP + RIGHT;
	while (bool(to_check) && !board->getPiece(to_check))
		to_check = to_check + UP + RIGHT;
	if (bool(to_check) && board->getPiece(to_check) && ((board->getPiece(to_check)->isBlack() && piece->isWhite()) || board->getPiece(to_check)->isWhite() && piece->isBlack()))
	{
		to_check = to_check + UP + RIGHT;
		if (bool(to_check) && !board->getPiece(to_check)) // Si la posición a moverse esta disponible y vacía.
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

	// [ | | | | ] // O: posición donde quedaría la pieza.
	// [ | | | | ] // X: posición de la pieza
	// [ | |X| | ] // +: posición a checkear para ver enemigo.
	// [ |+| | | ] // Nota: La distancia entre X y + puede ser tan amplia como se desee.
	// [o| | | | ]
	to_check = position + DOWN + LEFT;
	while (bool(to_check) && !board->getPiece(to_check))
		to_check = to_check + DOWN + LEFT;
	if (bool(to_check) && board->getPiece(to_check) && ((board->getPiece(to_check)->isBlack() && piece->isWhite()) || board->getPiece(to_check)->isWhite() && piece->isBlack()))
	{
		to_check = to_check + DOWN + LEFT;
		if (bool(to_check) && !board->getPiece(to_check)) // Si la posición a moverse esta disponible y vacía.
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

	// [ | | | | ] // O: posición donde quedaría la pieza.
	// [ | | | | ] // X: posición de la pieza
	// [ | |X| | ] // +: posición a checkear para ver enemigo.
	// [ | | |+| ] // Nota: La distancia entre X y + puede ser tan amplia como se desee.
	// [ | | | |o]
	to_check = position + DOWN + RIGHT;
	while (bool(to_check) && !board->getPiece(to_check))
		to_check = to_check + DOWN + RIGHT;
	if (bool(to_check) && board->getPiece(to_check) && ((board->getPiece(to_check)->isBlack() && piece->isWhite()) || board->getPiece(to_check)->isWhite() && piece->isBlack()))
	{
		to_check = to_check + DOWN + RIGHT;
		if (bool(to_check) && !board->getPiece(to_check)) // Si la posición a moverse esta disponible y vacía.
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

List<Weight> MovementController::weightMovements(List<Move> list)
{
	List<Weight> weights;
	Piece* piece;
	Weight weight;

	for (size_t i = 0; i < list.getSize(); i++)
	{
		weight = Weight();
		piece = board->getPiece(list[i].getSource());

		weight = weight - reconPosition(list[i].getSource(), piece);
		weight = weight + reconPosition(list[i].getDestination(), piece);
		weights.insert(weight);
	}

	return weights;
}

List<Weight> MovementController::weightMovements(List<Capture> list)
{

	List<Weight> weights;
	Piece* piece;
	Weight weight;

	for (size_t i = 0; i < list.getSize(); i++)
	{
		weight = Weight();
		piece = board->getPiece(list[i].getSource());

		weight = weight - reconPosition(list[i].getSource(), piece);
		weight = weight + reconPosition(list[i].getEnd(), piece);
		weights.insert(weight);
	}

	return weights;
}

Weight MovementController::reconPosition(Coord position, Piece* piece)
{
	Weight weight;
	// MODIFIERS
	// POSITION
	const Coord UP = { 1, 0 };
	const Coord DOWN = { -1, 0 };
	const Coord LEFT = { 0, -1 };
	const Coord RIGHT = { 0, 1 };
	// WEIGHT
	const Weight ICANBEEATEN = { 0,-10 };
	const Weight ENEMYNEAR = { 5, -5 };
	const Weight ICANTBEEATEN = { 0, 5 };
	const Weight TOWARDSTHEMOTHERLAND = { 10, 0 }; // Avanzar hacia el lado enemigo es bueno para el ataque.
	// --------
	Coord modifier;
	Coord to_check;
	Piece* potential_enemy;
	Coord to_eaten;

	// [o| | ] o = posición para fijarme si hay un enemigo.
	// [ |x| ] x = posición actual.
	// [ | |m] m = posición para ver si me pueden comer.
	modifier = Coord() + UP + LEFT;
	to_check = piece->getPosition() + modifier;
	potential_enemy = board->getPiece(to_check);
	to_eaten = piece->getPosition() + modifier.invert();

	if (bool(to_check))	// Si la posición es valida.
	{
		// Si el potencial enemigo existe
		if (potential_enemy)
		{
			// Si es un enemigo.
			if ((piece->isBlack() && potential_enemy->isWhite()) || (piece->isWhite() && potential_enemy->isBlack()))
			{
				weight += ENEMYNEAR;
				if (bool(to_eaten) && !board->getPiece(to_eaten))
				{
					weight += ICANBEEATEN;
				}
			}
			else
			{
				weight += ICANTBEEATEN;
			}
		}
		else
		{
			if (bool(to_eaten) && !board->getPiece(to_eaten))
			{
				// Se avanza en esa diagonal.
				to_check = position + modifier;
				while (bool(to_check) && !board->getPiece(to_check))
				{
					to_check = to_check + modifier;
				}
				// Si se encuentra una pieza, y esta está coronada.
				if (bool(to_check) && board->getPiece(to_check) && board->getPiece(to_check)->isCrowned())
				{
					// Y esa pieza es un enemigo.
					if ((piece->isBlack() && board->getPiece(to_check)->isWhite()) || (piece->isWhite() && board->getPiece(to_check)->isBlack()))
					{
						weight += ICANBEEATEN;
					}
				}
			}
		}
	}
	else
	{
		weight += ICANTBEEATEN;

		// Hay posibilidades de avanzar!
		if (piece->isWhite())
		{
			weight += TOWARDSTHEMOTHERLAND;
		}
	}

	// [ | |o] o = posición para fijarme si hay un enemigo.
	// [ |x| ] x = posición actual.
	// [m| | ] m = posición para ver si me pueden comer.
	modifier = Coord() + UP + RIGHT;
	to_check = piece->getPosition() + modifier;
	potential_enemy = board->getPiece(to_check);
	to_eaten = piece->getPosition() + modifier.invert();

	if (bool(to_check))	// Si la posición es valida.
	{
		// Si el potencial enemigo existe
		if (potential_enemy)
		{
			// Si es un enemigo.
			if ((piece->isBlack() && potential_enemy->isWhite()) || (piece->isWhite() && potential_enemy->isBlack()))
			{
				weight += ENEMYNEAR;
				if (bool(to_eaten) && !board->getPiece(to_eaten))
				{
					weight += ICANBEEATEN;
				}
			}
			else
			{
				weight += ICANTBEEATEN;
			}
		}
		else
		{
			if (bool(to_eaten) && !board->getPiece(to_eaten))
			{
				// Se avanza en esa diagonal.
				to_check = position + modifier;
				while (bool(to_check) && !board->getPiece(to_check))
				{
					to_check = to_check + modifier;
				}
				// Si se encuentra una pieza, y esta está coronada.
				if (bool(to_check) && board->getPiece(to_check) && board->getPiece(to_check)->isCrowned())
				{
					// Y esa pieza es un enemigo.
					if ((piece->isBlack() && board->getPiece(to_check)->isWhite()) || (piece->isWhite() && board->getPiece(to_check)->isBlack()))
					{
						weight += ICANBEEATEN;
					}
				}
			}
		}
	}
	else
	{
		weight += ICANTBEEATEN;

		// Hay posibilidades de avanzar!
		if (piece->isWhite())
		{
			weight += TOWARDSTHEMOTHERLAND;
		}
	}

	// [ | |m] o = posición para fijarme si hay un enemigo.
	// [ |x| ] x = posición actual.
	// [o| | ] m = posición para ver si me pueden comer.
	modifier = Coord() + DOWN + LEFT;
	to_check = piece->getPosition() + modifier;
	potential_enemy = board->getPiece(to_check);
	to_eaten = piece->getPosition() + modifier.invert();

	if (bool(to_check))	// Si la posición es valida.
	{
		// Si el potencial enemigo existe
		if (potential_enemy)
		{
			// Si es un enemigo.
			if ((piece->isBlack() && potential_enemy->isWhite()) || (piece->isWhite() && potential_enemy->isBlack()))
			{
				weight += ENEMYNEAR;
				if (bool(to_eaten) && !board->getPiece(to_eaten))
				{
					weight += ICANBEEATEN;
				}
			}
			else
			{
				weight += ICANTBEEATEN;
			}
		}
		else
		{
			if (bool(to_eaten) && !board->getPiece(to_eaten))
			{
				// Se avanza en esa diagonal.
				to_check = position + modifier;
				while (bool(to_check) && !board->getPiece(to_check))
				{
					to_check = to_check + modifier;
				}
				// Si se encuentra una pieza, y esta está coronada.
				if (bool(to_check) && board->getPiece(to_check) && board->getPiece(to_check)->isCrowned())
				{
					// Y esa pieza es un enemigo.
					if ((piece->isBlack() && board->getPiece(to_check)->isWhite()) || (piece->isWhite() && board->getPiece(to_check)->isBlack()))
					{
						weight += ICANBEEATEN;
					}
				}
			}
		}
	}
	else
	{
		weight += ICANTBEEATEN;

		// Hay posibilidades de avanzar!
		if (piece->isBlack())
		{
			weight += TOWARDSTHEMOTHERLAND;
		}
	}

	// [m| | ] o = posición para fijarme si hay un enemigo.
	// [ |x| ] x = posición actual.
	// [ | |o] m = posición para ver si me pueden comer.
	modifier = Coord() + DOWN + RIGHT;
	to_check = piece->getPosition() + modifier;
	potential_enemy = board->getPiece(to_check);
	to_eaten = piece->getPosition() + modifier.invert();

	if (bool(to_check))	// Si la posición es valida.
	{
		// Si el potencial enemigo existe
		if (potential_enemy)
		{
			// Si es un enemigo.
			if ((piece->isBlack() && potential_enemy->isWhite()) || (piece->isWhite() && potential_enemy->isBlack()))
			{
				weight += ENEMYNEAR;
				if (bool(to_eaten) && !board->getPiece(to_eaten))
				{
					weight += ICANBEEATEN;
				}
			}
			else
			{
				weight += ICANTBEEATEN;
			}
		}
		else
		{
			if (bool(to_eaten) && !board->getPiece(to_eaten))
			{
				// Se avanza en esa diagonal.
				to_check = position + modifier;
				while (bool(to_check) && !board->getPiece(to_check))
				{
					to_check = to_check + modifier;
				}
				// Si se encuentra una pieza, y esta está coronada.
				if (bool(to_check) && board->getPiece(to_check) && board->getPiece(to_check)->isCrowned())
				{
					// Y esa pieza es un enemigo.
					if ((piece->isBlack() && board->getPiece(to_check)->isWhite()) || (piece->isWhite() && board->getPiece(to_check)->isBlack()))
					{
						weight += ICANBEEATEN;
					}
				}
			}
		}
	}
	else
	{
		weight += ICANTBEEATEN;

		// Hay posibilidades de avanzar!
		if (piece->isBlack())
		{
			weight += TOWARDSTHEMOTHERLAND;
		}
	}

	return weight;
}



