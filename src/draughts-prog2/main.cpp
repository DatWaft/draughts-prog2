#include <iostream>
#include <string>
#include <sstream>

using namespace std;

#include "Node.h"
#include "List.h"
#include "Board.h"
#include "Move.h"
#include "Capture.h"

int main()
{
	Board* board = new Board;

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
		for (int j = 1; j <= board->MAX; j++)
		{
			cout << "[" << board->getSprite({ i,j }) << "]";
		}
		cout << endl;
	}

	delete board;
	system("pause");
}