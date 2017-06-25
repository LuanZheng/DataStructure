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
	/*��ʼʱ����һ������,�������ж���PriorityQueueLinkList<T, capacity> *linkList = NULL;
	����,�̳й����ķ���isEmpty(), isFull()����ʹ�õ�linkList���Ǹ����linkList,��ɴ���.
	ԭ����,C++���������ȹ��츸��ṹ,֮���ٹ�������ṹ.���̳й����ĺ����ڹ��츸���ʱ��
	��ȷ����.�䲢��֪������ĳ�Ա����,��˾��޷�����.*/
	return ((PriorityQueueLinkList<T, capacity>*)linkList)->enqueueWithPriority(data);
}