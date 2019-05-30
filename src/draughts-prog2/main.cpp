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
	b.setPiece({ 8,1 }, new Men(Piece::white));
	b.setPiece({ 7,2 }, new King(Piece::black));
	b.setPiece({ 1,8 }, new Men(Piece::black));
	b.setPiece({ 2,7 }, new King(Piece::white));
	b.setPiece({ 4,4 }, new King(Piece::black));
	for (size_t i = b.MAX; i > 0; i--)
	{
		cout << abs(int(i - 8));
		for (size_t j = 1; j <= b.MAX; j++)
			cout << "[" << b.getSprite(i, j) << "]";
		cout << endl;
	}
	cout << "  1  2  3  4  5  6  7  8" << endl;

	system("pause");

	cout << "b.upgradePiece({ 1,8 }: " << (b.upgradePiece({ 1,8 }) ? "True" : "False") << endl;
	cout << "b.upgradePiece({ 8,1 }: " << (b.upgradePiece({ 8,1 }) ? "True" : "False") << endl;
	cout << "b.upgradePiece({ 4,4 }: " << (b.upgradePiece({ 4,4 }) ? "True" : "False") << endl;
	cout << "b.upgradePiece({ 2,2 }: " << (b.upgradePiece({ 2,2 }) ? "True" : "False") << endl;
		
	system("pause");
	for (size_t i = b.MAX; i > 0; i--)
	{
		cout << abs(int(i - 8));
		for (size_t j = 1; j <= b.MAX; j++)
			cout << "[" << b.getSprite(i, j) << "]";
		cout << endl;
	}
	cout << "  1  2  3  4  5  6  7  8" << endl;

	cout << "b.search(b.getPiece(8,1)): " << b.search(b.getPiece(8, 1)) << endl;
	cout << "b.search(nullptr): " << b.search(nullptr) << endl;
 	system("pause");
}