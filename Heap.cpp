#include "Heap.h"

template <class T, unsigned int capacity>
Heap<T, capacity>::Heap()
{
	elemNum = 0;
	heapArray = new HeapNode<T>*[capacity];
}

template <class T, unsigned int capacity>
Heap<T, capacity>::~Heap()
{
	if (elemNum > 0)
	{
		for (int i = 0; i < elemNum; i++)
		{
			delete heapArray[i];
			heapArray[i] = NULL;
		}
	}
	if (NULL != heapArray)
	{
		delete[] heapArray;
		heapArray = NULL;
	}
	elemNum = 0;
}

template <class T, unsigned int capacity>
bool Heap<T, capacity>::isEmpty()
{
	bool result = false;
	if (0 == elemNum)
	{
		result = true;
	}
	else
	{
		result = false;
	}
	return result;
}

template <class T, unsigned int capacity>
bool Heap<T, capacity>::isFull()
{
	bool result = false;
	if (capacity == elemNum)
	{
		result = true;
	}
	else
	{
		result = false;
	}
	return result;
}

template <class T, unsigned int capacity>
TimeAndSpace Heap<T, capacity>::AddElem(T value)
{
	TimeAndSpace timeAndSpace;
	if (isFull())
	{
		//Do nothing
	}
	else
	{
		HeapNode<T>* node = new HeapNode<T>();
		node->data = value;
		if (isEmpty())
		{
			heapArray[0] = node;
			elemNum++;
		}
		else
		{
			heapArray[elemNum] = node;
			int parentIndex = (elemNum - 1) / 2;
			int childIndex = elemNum;
			while (parentIndex >= 0)   //has parent
			{
				(timeAndSpace.times)++;
				bool hasSwap = false;
				if (heapArray[childIndex]->data > heapArray[parentIndex]->data)
				{
					T temp = heapArray[parentIndex]->data;
					heapArray[parentIndex]->data = heapArray[childIndex]->data;
					heapArray[childIndex]->data = temp;
					hasSwap = true;
					(timeAndSpace.moves)++;
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
	return timeAndSpace;
}

template <class T, unsigned int capacity>
TimeAndSpace Heap<T, capacity>::deleteElem(T& value)
{
	TimeAndSpace timeAndSpace;
	if (isEmpty())
	{
		//Do nothing
	}
	else
	{
		value = heapArray[0]->data;
		//Copy last value to root, delete last memory
		heapArray[0]->data = heapArray[elemNum - 1]->data;
		delete heapArray[elemNum - 1];
		heapArray[elemNum - 1] = NULL;
		elemNum--;
		//move deap
		int index = 0;

		while (index * 2 + 1 < elemNum)
		{
			(timeAndSpace.times)++;
			bool hasSwap = false;
			if (index * 2 + 2 < elemNum)  //Both has left and right
			{
				//compare 3 elem, index, index*2+1 & index*2+2
				if (heapArray[index * 2 + 1]->data > heapArray[index * 2 + 2]->data)   //Left is big
				{
					if (heapArray[index]->data < heapArray[index * 2 + 1]->data)
					{
						//swap
						T temp = heapArray[index]->data;
						heapArray[index]->data = heapArray[index * 2 + 1]->data;
						heapArray[index * 2 + 1]->data = temp;
						hasSwap = true;
						index = index * 2 + 1;
						(timeAndSpace.moves)++;
					}
					else
					{
						break;
					}
				}
				else  //Right is big
				{
					if (heapArray[index]->data < heapArray[index * 2 + 2]->data)
					{
						//swap
						T temp = heapArray[index]->data;
						heapArray[index]->data = heapArray[index * 2 + 2]->data;
						heapArray[index * 2 + 2]->data = temp;
						hasSwap = true;
						index = index * 2 + 2;
						(timeAndSpace.moves)++;
					}
					else
					{
						break;
					}
				}
			}
			else  //only has left
			{
				//compare 2 elem, index & index*2+1, index*2+1 must leaf node, after compare, no need loop
				if (heapArray[index]->data < heapArray[index * 2 + 1]->data)
				{
					T temp = heapArray[index]->data;
					heapArray[index]->data = heapArray[index * 2 + 1]->data;
					heapArray[index * 2 + 1]->data = temp;
					(timeAndSpace.moves)++;
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

	return timeAndSpace;
}