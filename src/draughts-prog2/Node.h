#pragma once

template<class T>
class Node
{
private:
	T data;
	Node<T>* next;
	Node<T>* prev;
public:
	Node(T);
	Node(const Node<T>&);
	~Node();
	void operator=(const Node<T>&);

	Node<T>* getNext();
	Node<T>* getPrev();
	T& getData();

	Node<T>* createNext(T);
	Node<T>* createPrev(T);

	bool deleteNext();
	bool deletePrev();

	T& operator *();
	T* operator ->();
};

template<class T>
inline Node<T>::Node(T data)
{
	this->data = data;
	this->prev = nullptr;
	this->next = nullptr;
}

template<class T>
inline Node<T>::Node(const Node<T>& node)
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
inline void Node<T>::operator=(const Node<T>& node)
{
		this->data = node.data;
		this->prev = node.prev;
		this->next = node.next;
}

template<class T>
inline Node<T>* Node<T>::getNext()
{
	return this->next;
}

template<class T>
inline Node<T>* Node<T>::getPrev()
{
	return this->prev;
}

template<class T>
inline T& Node<T>::getData()
{
	return this->data;
}

template<class T>
inline Node<T>* Node<T>::createNext(T data)
{
	Node<T>* aux = new Node(data);
	aux->next = this->next;
	aux->prev = this;

	
	this->next = aux;
	if(aux->next)
		aux->next->prev = aux;
	return aux;
}

template<class T>
inline Node<T>* Node<T>::createPrev(T data)
{
	Node<T>* aux = new Node(data);
	aux->next = this;
	aux->prev = this->prev;

	this->prev = aux;
	if(aux->prev)
		aux->prev->next = aux;
	return aux;
}

template<class T>
inline bool Node<T>::deleteNext()
{
	if(!this->next)
		return false;
	
	Node<T>* aux = this->next;
	this->next = aux->next;
	if(aux->next)
		aux->next->prev = this;
	delete aux;
	return true;
}

template<class T>
inline bool Node<T>::deletePrev()
{
	if (!this->prev)
		return false;

	Node<T>* aux = this->prev;
	this->prev = aux->prev;
	if (aux->prev)
		aux->prev->next = this;
	delete aux;
	return true;
}

template<class T>
inline T& Node<T>::operator*()
{
	return this->data;
}

template<class T>
inline T* Node<T>::operator->()
{
	return &(this->data);
}
