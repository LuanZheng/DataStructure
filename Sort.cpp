#include "Sort.h"
#include "Heap.h"
#include "Heap.cpp"
#include <time.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

template<typename T, unsigned int size>
Sort<T, size>::Sort()
{
	loopTimes = 0;
	moveTimes = 0;
}

template<typename T, unsigned int size>
Sort<T, size>::~Sort()
{

}


//Dierect Insert Sort
//1. Stable
//2. Compare times will different as original sequence different, O(n2)
//3. Move times will different as original sequence different, O(n2)
//4. Terminate condition: inner loop, new value not small than compared value
template<typename T, unsigned int size>
void Sort<T,size>::directInsertSort(T* const sortArray/*, const unsigned int size*/)
{
	for (unsigned int i = 0; i < size; i++)
	{
		T flag = sortArray[i];
		for (unsigned int j = i - 1; j >= 0; j--)
		{
			loopTimes++;
			if (flag < sortArray[j])
			{
				sortArray[j + 1] = sortArray[j];
				sortArray[j] = flag;
				moveTimes++;
			}
			else
			{
				break;
			}
		}
	}
}


//Simple Select Sort
//1. Not Stable
//2. Compare times will identical as original sequence different, O(n2)
//3. Move times will different as original sequence different, O(n)
//4. Terminate condition: none
template<typename T, unsigned int size>
void Sort<T, size>::simpleSelectSort(T* const sortArray/*, const unsigned int size*/)
{
	T smallest;
	for (unsigned int i = 0; i < size; i++)
	{
		smallest = sortArray[i];
		int smallestFlag = i;
		for (unsigned int j = i+1; j < size; j++)
		{			
			loopTimes++;
			if (sortArray[j] < smallest)
			{
				smallest = sortArray[j];
				smallestFlag = j;
			}
		}
		if (smallestFlag != i)
		{
			T temp = sortArray[i];
			sortArray[i] = sortArray[smallestFlag];
			sortArray[smallestFlag] = temp;
			moveTimes++;
		}
	}
}

//Bubble sort
//1. Stable
//2. Time complecity, O(n2)
//3. Space complecity, O(n2)
//4. Terminate condition, during one time compare, no change happens
template <typename T, unsigned int size>
void Sort<T,size>::bubbleSort(T* const sortArray/*, const unsigned int size*/)
{
	bool hasSwap = false;
	for (unsigned int i = 0; i < size; i++)
	{
		hasSwap = false;
		for (unsigned int j = size-1; j > i; j--)
		{
			loopTimes++;
			if (sortArray[j] < sortArray[j-1])
			{
				T temp = sortArray[j];
				sortArray[j] = sortArray[j - 1];
				sortArray[j - 1] = temp;
				hasSwap = true;
				moveTimes++;
			}
		}
		if (!hasSwap)
			break;
	}
	return;
}


//Combsort
//1. Stable
//2. Time complex O(n2)
//3. Space complecity, O(n2)
//4. Terminate condition, for first stage, step become 1, for second stage, during one time compare, no change happens

template<typename T, unsigned int size>
void Sort<T, size>::combSort(T* const sortArray/*, const unsigned int size*/)
{
	//First stage
	unsigned int step = size / 1.3;
	while (step > 1)
	{
		for (unsigned int i = size - 1; i >= step; i--)
		{
			if (sortArray[i] < sortArray[i - step])
			{
				T temp = sortArray[i];
				sortArray[i] = sortArray[i - step];
				sortArray[i - step] = temp;
				moveTimes++;
			}
			loopTimes++;
		}
		step = step / 1.3;
	}

	//Second stage
	bool hasSwap = false;
	for (unsigned int i = 0; i < size; i++)
	{
		hasSwap = false;
		for (unsigned int j = size - 1; j > i; j--)
		{
			loopTimes++;
			if (sortArray[j] < sortArray[j - 1])
			{
				T temp = sortArray[j];
				sortArray[j] = sortArray[j - 1];
				sortArray[j - 1] = temp;
				hasSwap = true;
				moveTimes++;
			}
		}
		if (!hasSwap)
		{
			break;
		}
	}
}

//Combsort
//1. Not Stable
//2. Time complex O(n1.3)
//3. Space complecity, ?
//4. Terminate condition, increase step decrease to 1
template <typename T, unsigned int size>
void Sort<T,size>::shellSort(T* const sortArray/*, const unsigned int size*/)
{
	if (size < 10)
	{
		cout << "The array is so small, no need shell Sort, use direct insert sort is fine!" << endl;
		directInsertSort(sortArray, size);
	}
	else
	{
		int increaseArray[20]; //This could support to the max unsigned int in 32bit program
		int h = 1;
		int increaseArrayNum = 0;
		for (int i = 0; h < size; i++)
		{
			//loopTimes++;
			increaseArray[i] = h;
			h = 3 * h + 1;
			increaseArrayNum++;
		}

		for (int i = increaseArrayNum - 2; i >= 0; i--)
		{
			int increaseStep = increaseArray[i];
			for (int j = 0; j < increaseStep; j++)
			{
				for (int k = j + increaseStep; k < size; k = k + increaseStep)
				{
					T insertValue = sortArray[k];
					for (int l = k; (l - increaseStep) >= 0; l = l - increaseStep)
					{
						loopTimes++;						
						if (sortArray[l] < sortArray[l - increaseStep])
						{
							sortArray[l] = sortArray[l - increaseStep];
							sortArray[l - increaseStep] = insertValue;
							moveTimes++;
						}
						else
						{
							break;
						}
					}
				}
			}
		}

	}
	return;
}


//Heapsort
//1. Not Stable
//2. Time complex O(nlog(n))
//3. Space complecity, O(nlog(n))
//4. No special
template <typename T, unsigned int size>
void Sort<T,size>::heapSort(T * const sortArray/*, const unsigned int size*/)
{
	Heap<T, size> heap;
	TimeAndSpace timeAndSpace;
	//Construct the heap
	for (unsigned int i = 0; i < size; i++)
	{
		timeAndSpace = heap.AddElem(sortArray[i]);
		loopTimes += timeAndSpace.times;
		moveTimes += timeAndSpace.moves;
		
	}
	for (unsigned int i = 0; i < size; i++)
	{
		T value;
		timeAndSpace = heap.deleteElem(value);
		loopTimes += timeAndSpace.times;
		moveTimes += timeAndSpace.moves;
		sortArray[size - 1 - i] = value;
	}
	return;
}


//Quicksort
//1. Not Stable
//2. Time complex O(nlog(n))
//3. Space complecity, O(nlog(n))
//4. In one time quick sort, when low>=high, stop
template <typename T, unsigned int size>
void Sort<T, size>::quickSort(int low,  int high, T* const sortArray)
{
	if (low >= high)
	{

	}
	else
	{
		int startLowIndex = low;
		int startHighIndex = high;
		//T dataFlag = sortArray[low];
		while (low < high)
		{
			while ((low < high) && (sortArray[high] >= sortArray[low]))
			{
				loopTimes++;
				high--;
			}
			if (low >= high)
			{
				break;
			}
			else
			{
				T temp = sortArray[high];
				sortArray[high] = sortArray[low];
				sortArray[low] = temp;
				moveTimes++;
				low++;
			}

			while ((low < high) && (sortArray[low] <= sortArray[high]))
			{
				loopTimes++;
				low++;
			}
			if (low >= high)
			{
				break;
			}
			else
			{
				T temp = sortArray[low];
				sortArray[low] = sortArray[high];
				sortArray[high] = temp;
				moveTimes++;
				high--;
			}
		}
		//Be careful for low-1 and low+1, if forget the +1 or -1, will result dead loop
		quickSort(startLowIndex, low - 1, sortArray);
		quickSort(low + 1, startHighIndex, sortArray);
	}
	return;
}


//Mergesort
//1. Stable
//2. Time complex O(nlog(n))
//3. Need addition space's help (tempArray)
//4. In one time merge sort, when low>=high, stop
template <typename T, unsigned int size>
void Sort<T, size>::mergeSort(T* const sortArray, int low, int high)
{
	if (low >= high)
	{

	}
	else
	{
		int mid = (low + high) / 2;
		mergeSort(sortArray, low, mid);
		mergeSort(sortArray, mid + 1, high);
		merge(sortArray, low, high);
	}
	return;
}


template <typename T, unsigned int size>
void Sort<T, size>::merge(T* const sortArray, int low, int high)
{
	T* tempArray = new T[high-low+1];
	int mid = (low + high) / 2;
	int i = low;
	int j = mid + 1;
	int tempArrayIndex = 0;
	while ((i <= mid) && (j <= high))
	{
		loopTimes++;
		if (sortArray[i] <= sortArray[j])
		{
			tempArray[tempArrayIndex] = sortArray[i];
			i++;
			tempArrayIndex++;
		}
		else
		{
			tempArray[tempArrayIndex] = sortArray[j];
			j++;
			tempArrayIndex++;
		}
	}

	if (i > mid)
	{
		while (j <= high)
		{
			loopTimes++;
			tempArray[tempArrayIndex] = sortArray[j];
			j++;
			tempArrayIndex++;
		}
	}
	else if (j > high)
	{
		while (i <= mid)
		{
			loopTimes++;
			tempArray[tempArrayIndex] = sortArray[i];
			i++;
			tempArrayIndex++;
		}
	}

	//tempArrayIndex = 0;
	//for (int i = low; i <= high; i++)
	//{
	//	sortArray[i] = tempArray[tempArrayIndex];
	//	tempArrayIndex++;
	//}

	memset(&sortArray[low], 0, sizeof(T) * (high-low+1));
	memcpy(&sortArray[low], tempArray, sizeof(T) * (high-low+1));
	delete[] tempArray;
	tempArray = NULL;
	return;
}















//
//void Sort::merge(int low, int high)
//{
//	int* tempArray = new int[high-low + 1];
//	memset(tempArray, 0, (high - low + 1)*sizeof(int));
//	int mid = (low + high) / 2;
//	//First array is from low to mid
//	//Second array is from mid+1 to high
//	int i = low;
//	int j = mid+1;
//	int tempArrayIndex = 0;
//	while ((i <= mid) && (j <= high))
//	{
//		loopTimes++;
//		if (a[i] < a[j])
//		{
//			tempArray[tempArrayIndex] = a[i];
//			tempArrayIndex++;
//			i++;
//		}
//		else
//		{
//			tempArray[tempArrayIndex] = a[j];
//			tempArrayIndex++;
//			j++;
//		}
//	}
//
//	if (i > mid)
//	{
//		while (j <= high)
//		{
//			loopTimes++;
//			tempArray[tempArrayIndex] = a[j];
//			tempArrayIndex++;
//			j++;
//		}
//	}
//	else if (j > high)
//	{
//		while (i <= mid)
//		{
//			loopTimes++;
//			tempArray[tempArrayIndex] = a[i];
//			tempArrayIndex++;
//			i++;
//		}
//	}
//	else
//	{
//		//impossible
//	}
//	tempArrayIndex = 0;
//	for (int i = low; i <= high; i++)
//	{
//		loopTimes++;
//		a[i] = tempArray[tempArrayIndex];
//		tempArrayIndex++;
//	}
//	delete[] tempArray;
//	tempArray = NULL;
//	return;
//}


template <typename T, unsigned int size>
void Sort<T, size>::print(T* const sortArray)
{
	for (unsigned int i = 0; i < size; i++)
	{
		if ((i != 0) && (i % 8 == 0))
		{
			cout << endl;
		}
		cout << sortArray[i] << "  ";
	}
	cout << endl;
	cout << endl;
	cout << "LoopTimes:" << loopTimes << endl;
	cout << "MoveTimes:" << moveTimes << endl;
}

