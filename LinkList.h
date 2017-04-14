#ifndef _LINK_LIST_H_
#define _LINK_LIST_H_

#include "Constant.h"

template<typename T> struct LinkNode
{
	T data;
	LinkNode* next;
};

template<typename T, const unsigned int capacity> 
class LinkList
{
public:
	LinkList();
	~LinkList();
	bool isEmpty();
	bool isFull();
	bool insertFromHead(T data);
	bool insertAtLocation(T data, unsigned int n);
	bool deleteFromHead();
	bool deleteFromHead(T& data);
	bool deleteAtLocation(unsigned int n);
	bool deleteViaData(T data);
	bool getFirst(T& data);
	unsigned int getSize();
	void print();
protected:
	unsigned int linkNodeNum;
	LinkNode<T> *head = NULL;
};


template <typename T, const unsigned int capacity>
class QueueLinkList : protected LinkList<T, capacity>
{
public:
	QueueLinkList();
	~QueueLinkList();
	bool enqueueAtTail(T data);
	bool dequeueAtFirst(T& data);
	bool isEmpty();
	bool isFull();
	//bool getHead(T& data);
protected:
	LinkNode<T> *tail = NULL;
};

template <typename T, const unsigned int capacity>
class PriorityQueueLinkList : public QueueLinkList<T, capacity>
{
public:
	PriorityQueueLinkList();
	~PriorityQueueLinkList();
	bool enqueueWithPriority(T data);
private:
	bool enqueueAtTail(T data);  //利用C++的隐藏,将尾插入方法隐藏,因为优先级队列不适用尾插入暴露在外面
};

#endif // !_LINK_LIST_H_

