#include <iostream>
#include <string>
#include <sstream>

using namespace std;

#include "Node.h"

int main()
{
	Node<int*> node(new int(10));
	node.createNext(new int(20));

	cout << *node.getData() << " " << *(node.getNext())->getData() << endl;

	system("pause");
}