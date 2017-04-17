#ifndef _HEAP_H_
#define _HEAP_H_

#include "Constant.h"


template <class T>
struct HeapNode
{
	T data;                 //data
};


template <class T, unsigned int capacity>
class Heap
{
public:
	Heap();
	~Heap();
	void AddElem(T value);
	void deleteElem(T &value);
	bool isFull();
	bool isEmpty();
private:
	HeapNode<T>** heapArray;
	unsigned int elemNum;
};

#endif
