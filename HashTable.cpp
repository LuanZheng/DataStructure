#include "HashTable.h"
#include <iostream>

using namespace std;


HashTable::HashTable()
{

}

HashTable::~HashTable()
{
	if (NULL == hashArray)
		return;
	for (int i = 0; i < key; i++)
	{
		Node* pList = &hashArray[i];
		while (pList->next != NULL)
		{
			Node* newNext = pList->next->next;
			delete pList->next;
			pList->next = newNext;
		}
	}
	delete[] hashArray;
	hashArray = NULL;
}

bool HashTable::saveIntoHashTable(unsigned int* const pArray, unsigned int length)
{
	if (NULL != hashArray)
		return false;

	if (length <= 0)
		return false;

	unsigned int maxValue = 0;

	for (int i = 0; i < length; i++)
	{
		if (maxValue < pArray[i])
		{
			maxValue = pArray[i];
		}
	}

	if (maxValue <= 0)
		return false;

	unsigned int maxPrime1 = findMaxPrime(length);
	unsigned int maxPrime2 = findMaxPrime(maxValue);

	key = maxPrime1 < maxPrime2 ? maxPrime1 : maxPrime2;
	hashArray = new Node[key];
	//memset(hashArray,-1,key*sizeof(Node));

	unsigned int* pTempArray = (unsigned int*)pArray;
	for (int i = 0; i < length; i++)
	{
		if (-1 == hashArray[(*pTempArray) % key].value)
		{
			hashArray[(*pTempArray) % key].value = *pTempArray;
			hashArray[(*pTempArray) % key].next = NULL;
		}
		else
		{
			//new node
			Node* newNode = new Node();
			newNode->value = *pTempArray;
			newNode->next = NULL;

			Node* pList = &hashArray[(*pTempArray) % key];

			while (NULL != pList->next)
			{
				pList = pList->next;
			}
			pList->next = newNode;
		}
		pTempArray++;
	}
	return true;
}

void HashTable::print()
{
	for (int i = 0; i < key; i++)
	{
		cout<<"Index="<<i<<"Value="<<hashArray[i].value<<endl;
		Node* pList = &hashArray[i];
		while (pList->next != NULL)
		{
			cout << "Has Next, next value=" << pList->next->value << endl;;
			pList = pList->next;
			
		}
	}
}

unsigned int HashTable::findMaxPrime(unsigned int length)
{
	if (length <= 2)
		return 0;
	unsigned int maxPrime = 2;
	unsigned int i, j;
	for (i = 2; i < length; i++)
	{
		bool isPrime = true;
		for (j = 2; j <= i/j + 1; j++)
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