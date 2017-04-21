#ifndef _SORT_H_
#define _SORT_H_

#include "Constant.h"

template <class T>
class Sort
{
public:
	Sort();
	~Sort();
	void directInsertSort(T* const sortArray, const unsigned int size);
	void simpleSelectSort(T* const sortArray, const unsigned int size);
	void bubbleSort(T* const sortArray, const unsigned int size);
	void combSort(T* const sortArray, const unsigned int size);
	void shellSort(T* const sortArray, const unsigned int size);
	//void quickSort(int low, int high);
	//void mergeSort(int low, int high);
	void print(T* const sortArray, const unsigned int size);
private:
	//void merge(int low, int high);
	//void initArray();
	//void directInsertSortForShellSort(int step, int startIndex);
	/*T a[SORT_ARRAY_SIZE];*/
	unsigned int loopTimes;
	unsigned int moveTimes;
};

#endif