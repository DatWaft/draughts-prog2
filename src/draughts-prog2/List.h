#pragma once
#include "Node.h"
#include "Exception.h"

template<class T>
class List
{
private:
	Node<T>* first;
	Node<T>* last;
	size_t size;
public:
	List();
	List(const List&);
	~List();
	void operator = (const List&);

	size_t getSize() const;
	bool empty() const;

	void insert(T, size_t);
	void insert(T);

	bool erase(size_t);
	bool erase();

	bool clear();

	T& operator [] (size_t);
private:
	void checkIndex(size_t);
};

template<class T>
inline List<T>::List()
{
	this->first = nullptr;
	this->last = nullptr;
}

template<class T>
inline List<T>::List(const List& list)
{
	for (auto i = 0; i < list.getSize(); i++)
		this->insert(list[i]);
}

template<class T>
inline List<T>::~List()
{
	this->clear();
}

template<class T>
inline void List<T>::operator=(const List& list)
{
	this->clear();
	for (auto i = 0; i < list.getSize(); i++)
		this->insert(list[i]);
}

template<class T>
inline size_t List<T>::getSize() const
{
	return this->size;
}

template<class T>
inline bool List<T>::empty() const
{
	return size == 0;
}

template<class T>
inline void List<T>::insert(T data, size_t index)
{
	this->checkIndex(index);

	if (this->empty())
	{
		this->first = new Node<T>(data);
		this->last = this->first;
	}
	else if(index == 0)
	{
		this->first = this->first->createPrev(data);
	}
	else
	{
		Node<T> aux = this->first;
		for (auto i = 0; i < index; i++)
			aux = aux->getNext();
		aux.createNext(data);
	}
}

template<class T>
inline void List<T>::insert(T data)
{
	if (this->empty())
	{
		this->first = new Node<T>(data);
		this->last = this->first;
	}
	else
	{
		this->last = this->last->createNext(data);
	}
}

template<class T>
inline bool List<T>::erase(size_t index)
{
	if (this->empty())
		return false;
	checkIndex(index);

	if (this->size == 1)
	{
		delete this->first;
		this->first = nullptr;
		this->last = nullptr;
	}
	else if (index == 0)
	{
		this->first = this->first->getNext();
		this->first->deletePrev();
	}
	else if (index == this->size - 1)
	{
		this->last = this->last->prev;
		this->last->deleteNext();
	}
	else
	{
		Node<T> aux = this->first;
		for (auto i = 0; i < index - 1; i++)
			aux = aux->getNext();
		aux.deleteNext();
	}
	return true;
}

template<class T>
inline bool List<T>::erase()
{
	if (this->empty())
		return false;
	if (this->size == 1)
	{
		delete this->first;
		this->first = nullptr;
		this->last = nullptr;
	}
	else
	{
		this->last = this->last->prev;
		this->last->deleteNext();
	}
}

template<class T>
inline bool List<T>::clear()
{
	while (this->erase());
}

template<class T>
inline T& List<T>::operator[](size_t index)
{
	checkIndex(index);
	Node<T> aux = this->first;
	for (auto i = 0; i < index; i++)
		aux = aux.getNext();
	return *aux;
}

template<class T>
inline void List<T>::checkIndex(size_t index)
{
	if (index < 0)
		throw Exception("Indice menor a 0.");
	if (index > this->size)
		throw Exception("Indice mayor a " + std::to_string(this->size) +".");
}
