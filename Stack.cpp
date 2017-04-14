#include "Stack.h"

template<typename T, unsigned int capacity> Stack<T, capacity>::Stack()
{
	if (NULL == linkList)
	{
		linkList = new LinkList<T, capacity>();
	}
}

template<typename T, unsigned int capacity> Stack<T, capacity>::~Stack()
{
	delete linkList;
	linkList = NULL;
}


template<typename T, unsigned int capacity> bool Stack<T, capacity>::push(T data)
{
	bool rs = false;
	if (isFull())
	{
		rs = false;
	}
	else
	{
		rs = linkList->insertFromHead(data);
	}
	return rs;
}

template<typename T, unsigned int capacity> bool Stack<T, capacity>::pop(T &data)
{
	bool rs = false;
	if (isEmpty())
	{
		rs = false;
	}
	else
	{
		rs = linkList->deleteFromHead(data);
	}
	return rs;
}

template<typename T, unsigned int capacity> bool Stack<T, capacity>::isFull()
{
	bool rs = false;
	if (capacity == linkList->getSize())
	{
		rs = true;
	}
	return rs;
}

template<typename T, unsigned int capacity> bool Stack<T, capacity>::isEmpty()
{
	bool rs = false;
	if (0 == linkList->getSize())
	{
		rs = true;
	}
	return rs;
}

template<typename T, unsigned int capacity> bool Stack<T, capacity>::topElem(T &data)
{
	bool rs = false;
	if (isEmpty())
	{
		rs = false;
	}
	else
	{
		rs = linkList->getFirst(data);
	}
	return rs;
}

template <typename T, unsigned int capacity> unsigned int Stack<T, capacity>::getSize()
{
	return linkList->getSize();
}