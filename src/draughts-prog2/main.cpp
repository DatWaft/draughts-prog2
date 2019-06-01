#include <iostream>
#include <string>
#include <sstream>

using namespace std;

#include "MovementController.h"
#include "ViewController.h"

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
	ViewController v;

	for (int i = 8; i >= 6; i--)
		for (int j = 1; j <= board->MAX; j++)
			if (board->darkened({ i,j }))
				board->setPiece({ i,j }, new Men(Piece::black));
	for (int i = 3; i >= 1; i--)
		for (int j = 1; j <= board->MAX; j++)
			if (board->darkened({ i,j }))
				board->setPiece({ i,j }, new Men(Piece::white));

	v.displayBoard(board);

	cout << showList<Move>(mc.getMovements(Piece::white), "w");
	cout << showList<Move>(mc.getMovements(Piece::black), "b");

	cout << endl;
	cout << "Move 61 52: " << (mc.move("61 52", Piece::black) ? "True" : "False") << endl;

	v.displayBoard(board);

	delete board;
	system("pause");
}