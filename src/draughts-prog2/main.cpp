#include <iostream>
#include <string>
#include <sstream>

using namespace std;

#include "Node.h"
#include "List.h"
#include "Board.h"
#include "Move.h"
#include "Capture.h"
#include "ViewController.h"

int main()
{
	Board* board = new Board;
	ViewController v;
	for (int i = 8; i >= 6; i--)
		for (int j = 1; j <= board->MAX; j++)
			if (board->darkened({ i,j }))
				board->setPiece({ i,j }, new Men(Piece::black));
	for (int i = 3; i >= 1; i--)
		for (int j = 1; j <= board->MAX; j++)
			if (board->darkened({ i,j }))
				board->setPiece({ i,j }, new Men(Piece::white));

	/*for (int i = board->MAX; i > 0; i--)
	{
		for (int j = 1; j <= board->MAX; j++)
		{
			cout << "[" << board->getSprite({ i,j }) << "]";
		}
		cout << endl;
	}*/

	//Capture c({1,1}, {2,2});
	//c.createSubsequent({ 3,3 })->createSubsequent({ 4,4 })->createSubsequent({ 5,5 });

	//cout << "c: '" << string(c) << "'" << endl;
	//cout << "bool(Coord(1,1)): " << (bool(Coord{1,1}) ? "True" : "False") << endl;
	v.displayBoard(board);

	delete board;
	system("pause");
}