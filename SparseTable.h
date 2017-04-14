#ifndef _SPARSE_TABLE_H_
#define _SPARSE_TABLE_H_

#include "Constant.h"

template<class T1, class T2> 
struct SparseLinkNode
{
	unsigned int firstDataIndex;
	T1 firstData;
	unsigned int secondDataIndex;
	T2 secondData;
	SparseLinkNode<T1, T2>* firstLevelNext;
	SparseLinkNode<T1, T2>* secondLevelNext;
};

template<class T1, class T2> 
struct IndexNode
{
	SparseLinkNode<T1, T2>* next;
};


template<class T1, class T2> 
class SparseTable
{
public:
	SparseTable();
	~SparseTable();
	bool insert(const unsigned int firstIndex, const T1 firstData, const unsigned int secondIndex, const T2 secondData);
	bool deleteViaIndex(const unsigned int firstIndex, const unsigned int secondIndex);
private:
	bool isOverStack(const unsigned int firstIndex, const unsigned int secondIndex);
	bool insertAtRow(const unsigned int firstIndex, const unsigned int secondIndex, SparseLinkNode<T1, T2> *node);
	bool insertAtCol(const unsigned int firstIndex, const unsigned int secondIndex, SparseLinkNode<T1, T2> *node);
	bool delAtRow(const unsigned int firstIndex, const unsigned int secondIndex);
	bool delAtCol(const unsigned int firstIndex, const unsigned int secondIndex);
	IndexNode<T1, T2> rowIndexNodeArray[SPARSE_TABLE_ROW];
	IndexNode<T1, T2> colIndexNodeArray[SPARSE_TABLE_COL];
};

#endif // !_SPARSE_TABLE_H_

