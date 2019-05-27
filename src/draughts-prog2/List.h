#pragma once
#include "Node.h"

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

	void insert(T, size_t);
	void insert(T);

	void erase(size_t);
	void erase();

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
	
}

template<class T>
inline List<T>::~List()
{
}

template<class T>
inline void List<T>::operator=(const List& list)
{
}

template<class T>
inline size_t List<T>::getSize() const
{
	return this->size;
}

template<class T>
inline void List<T>::insert(T data, size_t index)
{
}

template<class T>
inline void List<T>::insert(T data)
{
}

template<class T>
inline void List<T>::erase(size_t index)
{
}

template<class T>
inline void List<T>::erase()
{
}

template<class T>
inline bool List<T>::clear()
{
	return false;
}

template<class T>
inline T& List<T>::operator[](size_t index)
{
	// TODO: insertar una instrucción return aquí
}

template<class T>
inline void List<T>::checkIndex(size_t index)
{
	
}
