#include "RandomSelect.h"

RandomSelect::RandomSelect()
{

}

RandomSelect::~RandomSelect()
{

}

void RandomSelect::selectMaxAndMin(int *a, int length, int &maxIndex, int &minIndex)
{
	maxIndex = 0;
	minIndex = 0;
	int maxValue = a[0];
	int minValue = a[0];
	for (int i = 0; i < length/2; i++)
	{
		if (a[2*i] < a[2*i + 1])
		{
			if (a[2*i] < minValue)
			{
				minValue = a[2*i];
				minIndex = 2 * i;
			}
			if (a[2*i + 1] > maxValue)
			{
				maxValue = a[2*i + 1];
				maxIndex = 2 * i + 1;
			}
		}
		else
		{
			if (a[2*i] > maxValue)
			{
				maxValue = a[2*i];
				maxIndex = 2 * i;
			}
			if (a[2*i + 1] < minValue)
			{
				minValue = a[2*i + 1];
				maxIndex = 2 * i + 1;
			}
		}
	}
	if (length % 2 == 1)
	{
		if (a[length - 1] > maxValue)
		{
			maxValue = a[length-1];
			maxIndex = length - 1;
		}
		if (a[length - 1] < minValue)
		{
			minValue = a[length-1];
			minIndex = length - 1;
		}
	}
}

int RandomSelect::selectXthMinValue(int *a, int xth, int length)
{
	bool rs = validInputParams(a, xth, length);
	if (!rs)
		return -1;
	else
	{
		return selectXthMinValue(a, 0, length - 1, xth);
	}
}

int RandomSelect::selectXthMaxValue(int *a, int xth, int length)
{
	bool rs = validInputParams(a, xth, length);
	if (!rs)
		return -1;
	else
	{
		return selectXthMaxValue(a, 0, length - 1, xth);
	}
}

bool RandomSelect::validInputParams(int *a, int xth, int length)
{
	bool rs = true;
	if (length <= 0)
	{
		return false;
	}


	if (xth > length)
	{
		return false;
	}
	return rs;
}


int RandomSelect::selectXthMinValue(int* a, int p, int r, int xth)
{
	int q = partition(a, p, r);
	int k = q - p + 1;        //低区的元素个数，包括q
	if (k == xth)
	{
		return q;
	}
	else if (k < xth)
	{
		return selectXthMinValue(a, q + 1, r, xth - k);
	}
	else
	{
		return selectXthMinValue(a, p, q - 1, xth);
	}
}

int RandomSelect::selectXthMaxValue(int *a, int p, int r, int xth)
{
	int q = partition(a, p, r);
	int k = r - q + 1;
	if (k == xth)
	{
		return q;
	}
	else if (k < xth)
	{
		return selectXthMaxValue(a, p, q - 1, xth - k);
	}
	else
	{
		return selectXthMaxValue(a, q + 1, r, xth);
	}
}

int RandomSelect::partition(int* a, int p, int r)
{
	int keyIndex = r;
	int key = a[r];
	while (p <= r)
	{
		while (p <= r)
		{
			if (a[p] <= key)
			{
				p++;
			}
			else //swap p pointer and key
			{
				int temp = a[p];
				a[p] = key;
				a[keyIndex] = temp;
				keyIndex = p;
				break;
			}
		}

		while (p <= r)
		{
			if (a[r] >= key)
			{
				r--;
			}
			else //swap r pointer and key
			{
				int temp = a[r];
				a[r] = key;
				a[keyIndex] = temp;
				keyIndex = r;
				break;
			}
		}
	}
	return keyIndex;
}