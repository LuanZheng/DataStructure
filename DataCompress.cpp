#include "DataCompress.h"
#include <iostream>
#include <algorithm>

DataCompress::DataCompress()
{

}

DataCompress::~DataCompress()
{

}


bool DataCompress::BWTEncodeing(char* pOutFirstArray, char* pOutLastArray, int* pOutLastIndexSeq, const string &strInput)
{
	const int len = strInput.size();
	string *strArray = new string[len];
	
	//1. Circule shift
	for (int i = 0; i < len; i++)
	{
		strArray[i] = cyclicShift(strInput,i);
	}

	//2. sort
	sort(strArray, strArray + len);

	//3. set LastArray
	for (int i = 0; i < len; i++)
	{
		pOutFirstArray[i] = strArray[i][0];
		pOutLastArray[i] = strArray[i][len - 1];
	}

	if (NULL != strArray)
	{
		delete[] strArray;
		strArray = NULL;
	}
		
	return true;
}

bool DataCompress::BTWDecoding(char* pInFirstArray, char* pInLastArray, char* pOutOriginalArray)
{
	//1. get preSum
	int len = strlen(pInLastArray);
	int *pCheckPreSum = new int[len];
	memset(pCheckPreSum, 0, sizeof(int) * len);
	calculatePreSum(pCheckPreSum, pInLastArray, len);

	//2. Get preSum Index
	int *pPreSumIndex = new int[4];
	memset(pPreSumIndex, 0, sizeof(int) * 4);
	calculateFirstIndex(pInFirstArray, pPreSumIndex, len);

	//3. Get Last Seq
	int* pLastIndexSeq = new int[len];
	memset(pLastIndexSeq, 0, sizeof(int)*(len));

	getLastSeq(pInLastArray, pCheckPreSum, pPreSumIndex, pLastIndexSeq, len);

	//4. set out array
	for (int i = 0; i < len; i++)
	{
		pOutOriginalArray[i] = pInLastArray[pLastIndexSeq[len - i - 1]];
	}

	if (NULL != pCheckPreSum)
	{
		delete[] pCheckPreSum;
		pCheckPreSum = NULL;
	}

	if (NULL != pPreSumIndex)
	{
		delete[] pPreSumIndex;
		pPreSumIndex = NULL;
	}

	if (NULL != pLastIndexSeq)
	{
		delete[] pLastIndexSeq;
		pLastIndexSeq = NULL;
	}

	return true;
}

string DataCompress::cyclicShift(const string &strInput, int n)
{
	int len = strInput.length();
	if (n >= len)
	{
		n = n % len;
	}
	string firstStrPart = strInput.substr(0, n);
	string secondStrPart = strInput.substr(n);
	string resultStr = secondStrPart.append(firstStrPart);
	return resultStr;
}

void DataCompress::calculatePreSum(int *pOutPreSum, const char *pInLastArray, int len)
{
	int preA = 0;
	int preC = 0;
	int preG = 0;
	int preT = 0;

	for (int i = 0; i < len; i++)
	{
		switch (pInLastArray[i])
		{
		case 'A':
			pOutPreSum[i] = preA;
			preA++;
			break;
		case 'C':
			pOutPreSum[i] = preC;
			preC++;
			break;
		case 'G':
			pOutPreSum[i] = preG;
			preG++;
			break;
		case 'T':
			pOutPreSum[i] = preT;
			preT++;
			break;
		default:
			break;
		}
	}
}

void DataCompress::calculateFirstIndex(char *pInFirstArray, int *pOutFirstIndex, int len)
{
	for (int i = 0; i < len; i++)
	{
		switch (pInFirstArray[i])
		{
		case 'A':
			pOutFirstIndex[1]++;
			pOutFirstIndex[2]++;
			pOutFirstIndex[3]++;
			break;
		case 'C':
			pOutFirstIndex[2]++;
			pOutFirstIndex[3]++;
			break;
		case 'G':
			pOutFirstIndex[3]++;
			break;
		case 'T':
			break;
		default:
			break;
		}
	}
	return;
}

void DataCompress::getLastSeq(char* pInLastArray, int *pInCheckPreSum, int *pInPreSumIndex, 
	int *pInOutLastIndexSeq, int len)
{
	for (int i = 0; i < len; i++)
	{
		switch (pInLastArray[pInOutLastIndexSeq[i]])
		{
		case 'A':
			pInOutLastIndexSeq[i + 1] = pInPreSumIndex[0] + pInCheckPreSum[pInOutLastIndexSeq[i]] + 1;
			break;
		case 'C':
			pInOutLastIndexSeq[i + 1] = pInPreSumIndex[1] + pInCheckPreSum[pInOutLastIndexSeq[i]] + 1;
			break;
		case 'G':
			pInOutLastIndexSeq[i + 1] = pInPreSumIndex[2] + pInCheckPreSum[pInOutLastIndexSeq[i]] + 1;
			break;
		case 'T':
			pInOutLastIndexSeq[i + 1] = pInPreSumIndex[3] + pInCheckPreSum[pInOutLastIndexSeq[i]] + 1;
			break;
		default:
			break;
		}
	}
	return;
}