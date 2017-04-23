#ifndef _SORT_H_
#define _SORT_H_

#include "Constant.h"

template <class T, unsigned int size>
class Sort
{
public:
	Sort();
	~Sort();
	void directInsertSort(T* const sortArray);
	void simpleSelectSort(T* const sortArray);
	void bubbleSort(T* const sortArray);
	void combSort(T* const sortArray);
	void shellSort(T* const sortArray);
	void heapSort(T * const sortArray);
	void quickSort(int low, int high, T* const sortArray);
	//void mergeSort(int low, int high);
	void print(T* const sortArray);
private:
	//void merge(int low, int high);
	//void directInsertSortForShellSort(int step, int startIndex);
	unsigned int loopTimes;
	unsigned int moveTimes;
};

#endif