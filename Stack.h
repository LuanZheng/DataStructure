#ifndef _STACK_H_
#define _STACK_H_
#include "Constant.h"
#include "LinkList.h"
//#include "LinkList.cpp"

template<typename T, unsigned int capicity> 
class Stack
{
public:
	Stack();
	~Stack();
	bool push(T data);
	bool pop(T &data);
	bool topElem(T &data);
	unsigned int getSize();
	bool isEmpty();
	bool isFull();
private:
	LinkList<T, capicity> *linkList = NULL;
};

#endif // !_STACK_H_

