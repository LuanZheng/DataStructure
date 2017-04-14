#ifndef _HASH_TABLE_H_
#define _HASH_TABLE_H_
#include "Constant.h"

struct Node
{
	unsigned int value = -1;
	Node* next = NULL;
};

class HashTable
{
public:
	HashTable();
	~HashTable();
	bool saveIntoHashTable(unsigned int* const pArray, unsigned int length);
	void print();
private:
	unsigned int findMaxPrime(unsigned int length);
	unsigned int key;
	Node *hashArray = NULL;
};

#endif