#include "HashFunction.h"
#include <iostream>

unsigned int HashFunction::divHashFunc(unsigned int keyValue, unsigned int length)
{
	unsigned int divValue = findMaxPrime(length);
	unsigned int key = keyValue % divValue;
	return key;
}

unsigned int HashFunction::overlapHashFunc(unsigned int keyValue, unsigned int length)
{
	unsigned int divValue = findMaxPrime(length);
	unsigned int value = 0;
	unsigned int tmpValue = keyValue;
	while (tmpValue != 0)
	{
		value += tmpValue % 1000;
		tmpValue /= 1000;
	}
	unsigned int key = value % divValue;
	return key;
}

unsigned int HashFunction::squareMidHashFunc(unsigned int keyValue, unsigned int length)
{
	if (keyValue > 10000)
	{
		return -1;
	}
	unsigned int rsValue = 0;
	unsigned int squareValue = keyValue * keyValue;
	unsigned int dArray[10];
	memset(dArray, 0, sizeof(int)*10);
	int i = 0;
	while (squareValue != 0)
	{
		dArray[i] = squareValue % 10;
		squareValue /= 10;
		i++;
	}
	if (i <= 3)
	{
		for (int j = 0; j < i; j++)
		{
			rsValue += dArray[j] * pow(10, j);
		}
	}
	else
	{
		int thisPos = i / 2 - 1;
		for (int j = 0; j < 3; j++)
		{
			rsValue += dArray[thisPos] * pow(10, j);
			thisPos++;
		}
	}
	return rsValue;
}

//unsigned int HashFunction::selectHashFunc(unsigned int keyValue, unsigned int length)
//{
//	return 0;
//}

unsigned int HashFunction::findMaxPrime(unsigned int length)
{
	if (length <= 2)
		return 0;
	unsigned int maxPrime = 2;
	unsigned int i, j;
	for (i = 2; i < length; i++)
	{
		bool isPrime = true;
		for (j = 2; j <= i / j + 1; j++)
		{
			if ((0 == i%j) && (i != 2))
			{
				isPrime = false;
				break;
			}
		}
		if (isPrime)
		{
			maxPrime = i;
		}
	}
	return maxPrime;
}