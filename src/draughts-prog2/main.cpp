#include <iostream>
#include <string>
#include <sstream>

using namespace std;

#include "Node.h"
#include "List.h"
#include "Board.h"

int main()
{
	Board b;
	for (size_t i = 0; i < b.MAX; i++)
	{
		for (size_t j = 0; j < b.MAX; j++)
			cout << "[" << b.getSprite(b.board[i][j]->getX(),b.board[i][j]->getY()) << "]";
		cout << endl;
	}
		
	system("pause");
}