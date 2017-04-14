#include "Heap.h"

Heap::Heap()
{
	elemNum = 0;
}

bool Heap::isEmpty()
{
	if (NULL == heapArray[0])
		return true;
	return false;
}

bool Heap::isFull()
{
	if (HEAP_NODE_SIZE == elemNum)
	{
		return true;
	}
	return false;
}

void Heap::AddElem(int value)
{
	if (isFull())
	{
		return;
	}
	HeapNode* node = new HeapNode();
	node->data = value;
	if (isEmpty())
	{
		heapArray[0] = node;
		elemNum++;
	}
	else
	{
		//elemNum++;
		heapArray[elemNum] = node;
		int parentIndex = (elemNum - 1) / 2;
		int childIndex = elemNum;
		while (parentIndex >= 0)   //has parent
		{
			bool hasSwap = false;
			if (heapArray[childIndex]->data > heapArray[parentIndex]->data)
			{
				int temp = heapArray[parentIndex]->data;
				heapArray[parentIndex]->data = heapArray[childIndex]->data;
				heapArray[childIndex]->data = temp;
				hasSwap = true;
			}
			if (!hasSwap)
			{
				break;
			}
			else
			{
				childIndex = parentIndex;
				parentIndex = (parentIndex - 1) / 2;
			}
		}
		elemNum++;
	}
}

void Heap::deleteElem(int& value)
{
	if (isEmpty())
	{
		value = -999999;
		return;
	}

	else
	{
		value = heapArray[0]->data;
		heapArray[0]->data = heapArray[elemNum-1]->data;
		delete heapArray[elemNum - 1];
		heapArray[elemNum - 1] = NULL;
		elemNum--;
		//move deap
		int index = 0;
		int newRootValue = value;
		while (index * 2 + 1 < elemNum)
		{
			bool hasSwap = false;
			if (index * 2 + 2 < elemNum)
			{
				//compare 3 elem, index, index*2+1 & index*2+2
				if (heapArray[index * 2 + 1]->data > heapArray[index * 2 + 2]->data)
				{
					if (heapArray[index]->data < heapArray[index * 2 + 1]->data)
					{
						//swap
						int temp = heapArray[index]->data;
						heapArray[index]->data = heapArray[index * 2 + 1]->data;
						heapArray[index * 2 + 1]->data = temp;
						hasSwap = true;
						index = index * 2 + 1;
					}
					else
					{
						break;
					}
				}
				else
				{
					if (heapArray[index]->data < heapArray[index * 2 + 2]->data)
					{
						//swap
						int temp = heapArray[index]->data;
						heapArray[index]->data = heapArray[index * 2 + 2]->data;
						heapArray[index * 2 + 2]->data = temp;
						hasSwap = true;
						index = index * 2 + 2;
					}
					else
					{
						break;
					}
				}
			}
			else
			{
				//compare 2 elem, index & index*2+1, index*2+1 must leaf node, after compare, no need loop
				if (heapArray[index]->data < heapArray[index * 2 + 1]->data)
				{
					int temp = heapArray[index]->data;
					heapArray[index]->data = heapArray[index * 2 + 1]->data;
					heapArray[index * 2 + 1]->data = temp;
					break;
				}
				else
				{
					break;
				}
			}
			if (!hasSwap)
			{
				break;
			}
		}
	}
}