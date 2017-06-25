#ifndef _HEAP_H_
#define _HEAP_H_

#include "Constant.h"


template <class T>
struct HeapNode
{
	T data;                 //data
};

class TimeAndSpace
{
public:
	int times = 0;
	int moves = 0;
};


template <class T, unsigned int capacity>
class Heap
{
public:
	Heap();
	~Heap();
	TimeAndSpace AddElem(T value);
	TimeAndSpace deleteElem(T &value);
	bool isFull();
	bool isEmpty();
private:
	HeapNode<T>** heapArray;
	unsigned int elemNum;
};

#endif
