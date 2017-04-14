#include "LinkList.h"
#include <string>
#include <iostream>
using namespace std;


template<typename T, const unsigned int capacity> 
LinkList<T, capacity>::LinkList()
{
	linkNodeNum = 0;
	head = new LinkNode<T>;
	head->next = NULL;
	memset(head, 0, sizeof(head));
}

template<typename T, const unsigned int capacity> 
LinkList<T, capacity>::~LinkList()
{
	cout << "LinkList destructor called" << endl;
	LinkNode<T> *iter = head;
	LinkNode<T> *preIter = iter;
	while (NULL != preIter->next)
	{		
		iter = preIter->next;
		preIter->next = iter->next;
		//cout << iter->data << " will be deleted in destruct function." << endl;
		delete iter;
		iter = NULL;
	}
}

template<typename T, const unsigned int capacity> 
bool LinkList<T, capacity>::isEmpty()
{
	if (NULL == head->next)
		return true;
	return false;
}

template<typename T, const unsigned int capacity> 
bool LinkList<T, capacity>::isFull()
{
	if (capacity == linkNodeNum)
		return true;
	return false;
}

template<typename T, const unsigned int capacity> 
bool LinkList<T, capacity>::insertFromHead(T data)
{
	if (NULL == head)
	{
		head = new LinkNode<T>;
		head->next = NULL;
	}

	if (isFull())
	{
		return false;
	}

	LinkNode<T> *linkNode = new LinkNode<T>();
	linkNode->data = data;
	linkNode->next = NULL;
	LinkNode<T> *afterNode = head->next;
	head->next = linkNode;
	linkNode->next = afterNode;
	linkNodeNum++;
	return true;
}

//Insert data after nth node
template<typename T, const unsigned int capacity> 
bool LinkList<T, capacity>::insertAtLocation(T data, unsigned int n)
{
	if (isFull())
		return false;
	if (linkNodeNum < n)
	{
		return false;
	}
	else
	{
		//Insert after n
		LinkNode<T> *node = head;
		//Insert at last
		for (unsigned int i = 0; i < n; i++)
		{
			if (NULL != node->next)
			{
				node = node->next;
			}
			else
			{
				//need log the error
				return false;
			}
		}

		LinkNode<T> *linkNode = new LinkNode<T>();
		linkNode->data = data;
		linkNode->next = node->next;
		node->next = linkNode;
		linkNodeNum++;
	}
	return true;
}

template<typename T, const unsigned int capacity> 
bool LinkList<T, capacity>::deleteFromHead()
{
	bool rs = false;
	if (isEmpty())
	{
		rs = false;
	}
	else
	{
		LinkNode<T> *needRemoveNode = head->next;
		if (NULL == needRemoveNode)
		{
			rs = false;
		}
		else
		{
			LinkNode<T> *nextNode = needRemoveNode->next;
			head->next = nextNode;
			needRemoveNode->next = NULL;
			delete needRemoveNode;
			linkNodeNum--;
			rs = true;
		}
	}
	return rs;
}

template<typename T, const unsigned int capacity>
bool LinkList<T, capacity>::deleteFromHead(T& data)
{
	bool rs = false;
	if (isEmpty())
	{
		rs = false;
	}
	else
	{
		LinkNode<T> *needRemoveNode = head->next;
		if (NULL == needRemoveNode)
		{
			rs = false;
		}
		else
		{
			data = needRemoveNode->data;
			LinkNode<T> *nextNode = needRemoveNode->next;
			head->next = nextNode;
			needRemoveNode->next = NULL;
			delete needRemoveNode;
			linkNodeNum--;
			rs = true;
		}
	}
	return rs;
}

template<typename T, const unsigned int capacity> 
bool LinkList<T, capacity>::deleteAtLocation(unsigned int n)
{
	if (isEmpty())
	{
		return false;
	}
	if (n > linkNodeNum)
	{
		return false;
	}
	else
	{
		LinkNode<T> *needRemoveNode = head;
		LinkNode<T> *preNode = NULL;
		for (unsigned int i = 0; i < n; i++)
		{
			preNode = needRemoveNode;
			needRemoveNode = needRemoveNode->next;
			if (NULL == needRemoveNode)
			{
				return false;
			}
		}
		preNode->next = needRemoveNode->next;
		delete needRemoveNode;
		needRemoveNode = NULL;
		linkNodeNum--;
	}
	return true;
}

template<typename T, const unsigned int capacity> 
bool LinkList<T, capacity>::deleteViaData(T data)
{
	if (isEmpty())
	{
		return false;
	}
	bool isFind = false;
	LinkNode<T> *iter = head;
	while(NULL != iter->next)
	{
		LinkNode<T> *preNode = iter;
		iter = iter->next;
		try
		{
			if (data == iter->data)
			{
				preNode->next = iter->next;
				delete iter;
				iter = NULL;
				isFind = true;
				linkNodeNum--;
				break;
			}
		}
		catch (exception e)
		{
			cout << e.what() << endl;
			return false;
		}
	}
	return isFind;
}

template <typename T, const unsigned int capacity>
bool LinkList<T, capacity>::getFirst(T& data)
{
	bool rs = false;
	if (isEmpty())
	{
		rs = false;
	}
	else
	{
		if ((NULL == head) || (NULL == head->next))
		{
			rs = false;
		}
		else
		{
			data = head->next->data;
			rs = true;
		}
	}
	return rs;
}

template<typename T, const unsigned int capacity>
unsigned int LinkList<T, capacity>::getSize()
{
	return linkNodeNum;
}

template<typename T, const unsigned int capacity> 
void LinkList<T, capacity>::print()
{
	LinkNode<T>* iter = head;
	while (NULL != iter->next)
	{
		iter = iter->next;
		cout << iter->data << "  ";
	}
	cout << endl;

}

template<typename T, const unsigned int capacity>
QueueLinkList<T, capacity>::QueueLinkList()
{

}

template<typename T, const unsigned int capacity>
QueueLinkList<T, capacity>::~QueueLinkList()
{
	cout << "QueueLinkList destructor called" << endl;
}

template<typename T, const unsigned int capacity>
bool QueueLinkList<T, capacity>::enqueueAtTail(T data)
{
	bool rs = false;
	if (isFull())
	{
		rs = false;
	}
	else if (isEmpty())
	{
		LinkNode<T> *node = new LinkNode<T>();
		node->data = data;
		node->next = NULL;
		head->next = node;
		tail = node;
		linkNodeNum++;
		rs = true;
	}
	else
	{
		LinkNode<T> *node = new LinkNode<T>();
		node->data = data;
		node->next = NULL;
		tail->next = node;
		tail = node;
		linkNodeNum++;
		rs = true;
	}
	return rs;
}

template<typename T, const unsigned int capacity>
bool QueueLinkList<T, capacity>::dequeueAtFirst(T &data)
{
	bool rs = false;
	if (isEmpty())
	{
		rs = false;
	}
	else
	{
		rs = deleteFromHead(data);
		if (isEmpty())
		{
			tail = NULL;
		}
	}
	return rs;
}

template<typename T, const unsigned int capacity>
bool QueueLinkList<T, capacity>::isEmpty()
{
	return LinkList<T, capacity>::isEmpty();
}

template<typename T, const unsigned int capacity>
bool QueueLinkList<T, capacity>::isFull()
{
	return LinkList<T, capacity>::isFull();
}


template<typename T, const unsigned int capacity>
PriorityQueueLinkList<T, capacity>::PriorityQueueLinkList()
{

}

template<typename T, const unsigned int capacity>
PriorityQueueLinkList<T, capacity>::~PriorityQueueLinkList()
{
	cout << "PriorityQueueLinkList destructor called" << endl;
}



template<typename T, const unsigned int capacity>
bool PriorityQueueLinkList<T, capacity>::enqueueWithPriority(T data)
{
	bool rs = false;
	if (isFull())
	{
		rs = false;
	}
	else
	{
		if (isEmpty())
		{
			LinkNode<T> *node = new LinkNode<T>();
			node->data = data;
			node->next = NULL;
			head->next = node;
			tail = node;
			linkNodeNum++;
			rs = true;
		}
		else
		{
			LinkNode<T> *iter = head->next;
			LinkNode<T> *preIter = head;
			while (NULL != iter)
			{
				unsigned int priority = iter->data.priority;
				if (data.priority >= priority)
				{
					preIter = iter;
					iter = iter->next;
				}
				else
				{
					//insert after preIter and before iter
					LinkNode<T> *node = new LinkNode<T>();
					node->data = data;
					preIter->next = node;
					node->next = iter;
					linkNodeNum++;
					rs = true;
					break;
				}
			}
			if (NULL == iter)
			{
				rs = enqueueAtTail(data);
			}
		}
	}
	return rs;
}


template<typename T, const unsigned int capacity>
bool PriorityQueueLinkList<T, capacity>::enqueueAtTail(T data)
{
	return QueueLinkList<T, capacity>::enqueueAtTail(data);     //默认实现，目的在于隐藏该方法
}