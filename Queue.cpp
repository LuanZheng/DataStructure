#include "Queue.h"



template<typename T, unsigned int capacity> 
ArrayQueue<T,capacity>::ArrayQueue()
{
	readPtr = queue;
	writePtr = queue;
	readPtrLoop = 0;
	writePtrLoop = 0;
}

template<typename T, unsigned int capacity> 
ArrayQueue<T,capacity>::~ArrayQueue()
{
	readPtr = queue;
	writePtr = queue;
	readPtrLoop = 0;
	writePtrLoop = 0;
}

template<typename T, unsigned int capacity> 
bool ArrayQueue<T,capacity>::isEmpty()
{
	if ((writePtr == readPtr) && (writePtrLoop - readPtrLoop == 0))
		return true;
	return false;
}


template<typename T, unsigned int capacity>
bool ArrayQueue<T,capacity>::isFull()
{
	if ((writePtr == readPtr) && (writePtrLoop - readPtrLoop == 1))
	{
		return true;
	}
	return false;
}

template<typename T, unsigned int capacity> 
void ArrayQueue<T,capacity>::moveNext(QUEUE_PTR_FLAG rOrW)
{
	if (READ_PTR == rOrW)
	{
		if (isLast(rOrW))
		{
			readPtr = queue;
			readPtrLoop++;
		}
		else
		{
			readPtr++;
		}
	}
	else if (WRITE_PTR == rOrW)
	{
		if (isLast(rOrW))
		{
			writePtr = queue;
			writePtrLoop++;
		}
		else
		{
			writePtr++;
		}
	}
	return;
}


template<typename T, unsigned int capacity> 
bool ArrayQueue<T,capacity>::isLast(QUEUE_PTR_FLAG rOrW)
{
	if (READ_PTR == rOrW)
	{
		if (readPtr == &queue[QUEUE_SIZE-1])
		{
			return true;
		}
	}
	else if (WRITE_PTR == rOrW)
	{
		if (writePtr == &queue[QUEUE_SIZE-1])
		{
			return true;
		}
	}
	return false;
}

template<typename T, unsigned int capacity> 
bool ArrayQueue<T,capacity>::isFirst(QUEUE_PTR_FLAG rOrW)
{
	if (READ_PTR == rOrW)
	{
		if (readPtr == queue)
		{
			return true;
		}
	}
	else if (WRITE_PTR == rOrW)
	{
		if (writePtr == queue)
		{
			return true;
		}
	}
	return false;
}

template<typename T, unsigned int capacity>
void ArrayQueue<T, capacity>::enQueue(T item)
{
	if (isFull())
	{
		return;
	}
	*writePtr = item;
	moveNext(WRITE_PTR);
	return;
}

template<typename T, unsigned int capacity> 
void ArrayQueue<T,capacity>::deQueue(T &item)
{
	if (isEmpty())
	{
		return;
	}
	T value = *readPtr;
	item = value;
	moveNext(READ_PTR);
	return;
}


template<typename T, unsigned int capacity> 
LinkQueue<T, capacity>::LinkQueue()
{
	if (NULL == linkList)
	{
		linkList = new QueueLinkList<T, capacity>();
	}
}

template<typename T, unsigned int capacity> 
LinkQueue<T, capacity>::~LinkQueue()
{
	cout << "LinkQueue destructor called" << endl;
	if (isEmpty())
	{
		if (NULL != linkList)
		{
			delete linkList;
			linkList = NULL;
		}
	}
	else
	{
		T data;
		while (!isEmpty())
		{
			bool rs = deQueue(data);
			//cout << "use desturctor to release the memory. Data=";
			//cout << data << endl;
			if (!rs)
			{
				//Need Log fatal error
				cout << "fatal error! dequeue failed in destructor!" << endl;
				break;
			}
		}
		if (NULL != linkList)
		{
			delete linkList;
			linkList = NULL;
		}
	}
}

template<typename T, unsigned int capacity> 
bool LinkQueue<T,capacity>::isEmpty()
{
	bool rs = false;
	if (NULL == linkList)
	{
		rs = true;
	}
	else
	{
		rs = linkList->isEmpty();
	}
	return rs;
}

template<typename T, unsigned int capacity> 
bool LinkQueue<T, capacity>::isFull()
{
	bool rs = false;
	if (NULL == linkList)
	{
		rs = false;
	}
	else
	{
		rs = linkList->isFull();
	}
	return rs;
}

template<typename T, unsigned int capacity>
bool LinkQueue<T,capacity>::enQueue(T data)        //priority value less, priority higher
{
	bool rs = false;
	if (isFull())
	{
		rs = false;
	}
	else
	{
		rs = linkList->enqueueAtTail(data);
	}
	return rs;
}


template<typename T, unsigned int capacity> 
bool LinkQueue<T, capacity>::deQueue(T& data)
{
	bool rs = false;
	if (isEmpty())
	{
		rs = false;
	}
	else
	{
		rs = linkList->dequeueAtFirst(data);
	}
	return rs;
}

template <typename T, unsigned int capacity>
PriorityLinkQueue<T, capacity>::PriorityLinkQueue()
{
	if (NULL == linkList)
	{
		linkList = new PriorityQueueLinkList<T, capacity>();
	}
}

template <typename T, unsigned int capacity>
PriorityLinkQueue<T, capacity>::~PriorityLinkQueue()
{
	cout << "PriorityLinkQueue destructor called" << endl;
}

template <typename T, unsigned int capacity>
bool PriorityLinkQueue<T, capacity>::enQueue(T data)
{
	/*开始时犯了一个错误,在子类中定义PriorityQueueLinkList<T, capacity> *linkList = NULL;
	这样,继承过来的方法isEmpty(), isFull()等中使用的linkList仍是父类的linkList,造成错误.
	原因是,C++编译器会先构造父类结构,之后再构造子类结构.而继承过来的函数在构造父类的时候
	就确定了.其并不知道子类的成员变量,因此就无法访问.*/
	return ((PriorityQueueLinkList<T, capacity>*)linkList)->enqueueWithPriority(data);
}