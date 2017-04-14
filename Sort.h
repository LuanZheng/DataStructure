#ifndef _SORT_H_
#define _SORT_H_

#include "Constant.h"

class Sort
{
public:
	Sort();
	void directInsertSort();
	void simpleSelectSort();
	void bubbleSort();
	void combSort();
	void shellSort();
	void quickSort(int low, int high);
	void mergeSort(int low, int high);
	void print();
private:
	void merge(int low, int high);
	void initArray();
	void directInsertSortForShellSort(int step, int startIndex);
	int a[SORT_ARRAY_SIZE];
	int loopTimes;
	int moveTimes;
};

#endif