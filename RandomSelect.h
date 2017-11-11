#ifndef _RANDOM_SELECT_H_
#define _RANDOM_SELECT_H_

class RandomSelect
{
public:
	RandomSelect();
	~RandomSelect();
	//This function is select the max value and min value together
	void selectMaxAndMin(int *a, int length, int &max, int &min);
	//This function is select the Xth min value from pth to rth index in array a, 
	//return the index of the Xth min value
	int selectXthMinValue(int *a, int xth, int length);
	int selectXthMaxValue(int *a, int xth, int length);

private:
	int selectXthMinValue(int* a, int p, int r, int xth);
	int selectXthMaxValue(int *a, int p, int r, int xth);
	//This function is partition the array a, after exec, the array will partition
	//as 2 part, first part is p...q, second part is q+1 ... r, return the index value q
	int partition(int* a, int p, int r);
	bool validInputParams(int *a, int xth, int length);
};

#endif