#ifndef _HEAP_H_
#define _HEAP_H_

#include "Constant.h"

struct HeapNode
{
	int data;                 //data
};

class Heap
{
public:
	Heap();
	void AddElem(int value);
	void deleteElem(int& value);
	bool isFull();
	bool isEmpty();
private:
	HeapNode* heapArray[HEAP_NODE_SIZE];
	int elemNum;
};

#endif
