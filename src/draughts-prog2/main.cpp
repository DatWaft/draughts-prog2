#include <iostream>
#include <string>
#include <sstream>

using namespace std;

#include "MovementController.h"

template<class T>
string showList(List<T> v, string title)
{
	stringstream s;
	s << title << ": ";
	for (size_t i = 0; i < v.getSize(); i++)
		s << "[" << string(v[i]) << "]"; s << endl;
	return s.str();
}

int main()
{
	Board* board = new Board;
	MovementController mc (board);

	for (int i = 8; i >= 6; i--)
		for (int j = 1; j <= board->MAX; j++)
			if (board->darkened({ i,j }))
				board->setPiece({ i,j }, new Men(Piece::black));
	for (int i = 3; i >= 1; i--)
		for (int j = 1; j <= board->MAX; j++)
			if (board->darkened({ i,j }))
				board->setPiece({ i,j }, new Men(Piece::white));

	for (int i = board->MAX; i > 0; i--)
	{
		cout << i << " ";
		for (int j = 1; j <= board->MAX; j++)
		{
			cout << "[" << board->getSprite({ i,j }) << "]";
		}
		cout << endl;
	}
	cout << "   1  2  3  4  5  6  7  8" << endl;

	cout << showList<Move>(mc.getMovements(Piece::white), "w");
	cout << showList<Move>(mc.getMovements(Piece::black), "b");

	cout << endl;

	string move;
	cout << "Digite un movimiento: "; getline(cin, move);

	cout << "Move" << move << ": " << (mc.move(move, Piece::white) ? "True" : "False") << endl;

	for (int i = board->MAX; i > 0; i--)
	{
		cout << i << " ";
		for (int j = 1; j <= board->MAX; j++)
		{
			cout << "[" << board->getSprite({ i,j }) << "]";
		}
		cout << endl;
	}
	cout << "   1  2  3  4  5  6  7  8" << endl;

	delete board;
	system("pause");
}