#include "Sort.h"
#include <time.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

template<typename T>
Sort<T>::Sort()
{
	loopTimes = 0;
	moveTimes = 0;
}

template<typename T>
Sort<T>::~Sort()
{

}


//Dierect Insert Sort
//1. Stable
//2. Compare times will different as original sequence different, O(n2)
//3. Move times will different as original sequence different, O(n2)
//4. Terminate condition: inner loop, new value not small than compared value
template<typename T>
void Sort<T>::directInsertSort(T* const sortArray, const unsigned int size)
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
template<typename T>
void Sort<T>::simpleSelectSort(T* const sortArray, const unsigned int size)
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
template <typename T>
void Sort<T>::bubbleSort(T* const sortArray, const unsigned int size)
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





//
//void Sort::mergeSort(int low, int high)
//{
//	if (low >= high)
//		return;
//
//	int mid = (low + high) / 2;
//	mergeSort(low, mid);
//	mergeSort(mid + 1, high);
//	merge(low, high);
//}
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
//
//void Sort::quickSort(int low, int high)
//{
//	if (low >= high)
//		return;
//
//	int flag = a[low];
//	int i = low;
//	int j = high;
//	cout << "LOW=" << low << "HIGH=" << high << endl;
//	while (i < j)
//	{
//		while ((i < j) && (a[j] >= flag))   //= is very important, else it will result dead loop. i<j maybe for ever satisfy
//		{
//			loopTimes++;
//			j--;
//		}
//		a[i] = a[j];
//
//		while ((i<j) && (a[i] <= flag))
//		{
//			loopTimes++;
//			i++;
//		}
//		a[j] = a[i];
//	}
//	a[i] = flag;
//	quickSort(low, i - 1);
//	quickSort(i + 1, high);
//}


//void Sort::initArray()
//{
//	srand(time(0));
//	for (int i = 0; i < SORT_ARRAY_SIZE; i++)
//	{
//		a[i] = rand();
//	}
//	loopTimes = 0;
//	moveTimes = 0;
//}



//void Sort::directInsertSortForShellSort(int step, int startIndex)
//{
//	for (int i = startIndex; i < SORT_ARRAY_SIZE; i=i+step)
//	{
//		int flag = a[i];
//		for (int j = i - step; j >= 0; j = j - step)
//		{
//			loopTimes++;
//			if (flag < a[j])
//			{
//				a[j+step] = a[j];
//				a[j] = flag;
//				moveTimes++;
//			}
//			else
//			{
//				break;
//			}
//		}
//	}
//}
//
//
////Bubble Select Sort
////1. Stable
////2. Compare times will different as original sequence different, O(n2)
////3. Move times will different as original sequence different, O(n2)
////4. Terminate condition: outer loop, not swap happened during one time loop compare
//
//void Sort::bubbleSort()
//{
//	bool hasSwap = false;
//	for (int i = 0; i < SORT_ARRAY_SIZE; i++)
//	{
//		hasSwap = false;
//		for (int j = 0; j < SORT_ARRAY_SIZE - i - 1; j++)
//		{
//			loopTimes++;
//			if (a[j] > a[j + 1])
//			{
//				int temp = a[j];
//				a[j] = a[j + 1];
//				a[j + 1] = temp;
//				hasSwap = true;
//				moveTimes++;
//			}
//		}
//		if (!hasSwap)
//		{
//			break;
//		}
//	}
//}
//
//void Sort::combSort()
//{
//	int comb = SORT_ARRAY_SIZE / 1.3;
//	while (comb > 1)
//	{
//		for (int j = comb; j < SORT_ARRAY_SIZE; j++)
//		{
//			loopTimes++;
//			if (a[j - comb] > a[j])
//			{
//				//swap
//				int temp = a[j];
//				a[j] = a[j - comb];
//				a[j - comb] = temp;
//				moveTimes++;
//			}
//		}
//		comb = comb / 1.3;
//	}
//	//bubble sort
//	bubbleSort();
//}
//
//void Sort::shellSort()
//{
//	int increaseArrayLength = 0;
//	for (int i = 1; i < SORT_ARRAY_SIZE; i = 3 * i + 1)
//	{
//		increaseArrayLength++;
//	}
//	if (0 == increaseArrayLength)
//	{
//		return;
//	}
//	int *pIncreaseArray = new int[increaseArrayLength];
//	int *oriPointer = pIncreaseArray;
//	for (int i = 1; i < SORT_ARRAY_SIZE; i = 3 * i + 1)
//	{
//		*pIncreaseArray = i;
//		pIncreaseArray++;
//	}
//	pIncreaseArray = oriPointer;
//
//	for (int i = increaseArrayLength; i > 0; i--)
//	{
//		int step = pIncreaseArray[i-1];
//		for (int j = 0; j < step; j++)
//		{
//			directInsertSortForShellSort(step, j);
//		}
//		
//	}
//	delete pIncreaseArray;
//}

template <typename T>
void Sort<T>::print(T* const sortArray, const unsigned int size)
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

