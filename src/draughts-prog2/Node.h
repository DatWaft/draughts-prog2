#pragma once

template<class T>
class Node
{
private:
	T data;
	Node* next;
	Node* prev;
public:
	Node(T);
	Node(const Node&);
	~Node();
	void operator=(const Node&);

	Node* getNext();
	Node* getPrev();
	T getData();

	void createNext(T);
	void createPrev(T);

	bool deleteNext();
	bool deletePrev();
};

template<class T>
inline Node<T>::Node(T data)
{
	this->data = data;
	this->prev = nullptr;
	this->next = nullptr;
}

template<class T>
inline Node<T>::Node(const Node& node)
{
	this->data = node.data;
	this->prev = node.prev;
	this->next = node.next;
}

template<class T>
inline Node<T>::~Node()
{
}

template<class T>
inline void Node<T>::operator=(const Node& node)
{
	this->data = node.data;
	this->prev = node.prev;
	this->next = node.next;
}

