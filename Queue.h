#ifndef  _QUEUE_H_
#define _QUEUE_H_

#include "Constant.h"
#include "LinkList.h"

template<typename T> class ArrayQueue
{
public: 
	ArrayQueue();
	~ArrayQueue();
	void enQueue(T item); 
	bool isEmpty();
    void deQueue(T &item);

private:
	void moveNext(QUEUE_PTR_FLAG rOrW);
	bool isFull();
	bool isLast(QUEUE_PTR_FLAG rOrW);
	bool isFirst(QUEUE_PTR_FLAG rOrW);
	T* readPtr;
	T* writePtr;
	T queue[QUEUE_SIZE];
	int readPtrLoop;
	int writePtrLoop;
	//static T defaultValue;
};

template<typename T> struct LinkQueueNode
{  
	unsigned int priority;
	LinkNode<T> node;
};



template<typename T, unsigned int capacity> 
class LinkQueue
{
public:
	LinkQueue();
	~LinkQueue();
	bool enQueue(T data);
	bool deQueue(T& data);
	bool isEmpty();
	bool isFull();
protected:
	QueueLinkList<T, capacity> *linkList = NULL;
};

template<typename T, unsigned int capacity>
class PriorityLinkQueue : public LinkQueue<T, capacity>
{
public:
	PriorityLinkQueue();
	~PriorityLinkQueue();
	bool enQueue(T data);
//private:
//	PriorityQueueLinkList<T, capacity> *linkList = NULL;
};


#endif // ! _QUEUE_H_

