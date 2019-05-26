#include <iostream>
#include <string>

using namespace std;

#include "Node.h"

int main()
{
	Node<int>* node = new Node<int>(10);
	cout << "[" << node->getPrev() << "] <-- [" << node << "]-->[" << node->getNext() << "]" << endl;
	++node;
	cout << "[" << node->getPrev() << "] <-- [" << node << "]-->[" << node->getNext() << "]" << endl;
	system("pause");
}