#include "SparseTable.h"

template<class T1, class T2> 
SparseTable<T1, T2>::SparseTable()
{
	for (int i = 0; i < SPARSE_TABLE_ROW; i++)
	{
		rowIndexNodeArray[i].next = NULL;
	}
	for (int i = 0; i < SPARSE_TABLE_COL; i++)
	{
		colIndexNodeArray[i].next = NULL;
	}
}

template<class T1, class T2> 
SparseTable<T1, T2>::~SparseTable()
{
	for (int i = 0; i < SPARSE_TABLE_ROW; i++)
	{
		if (NULL == rowIndexNodeArray[i].next)
		{
			continue;
		}
		else
		{
			SparseLinkNode<T1, T2>* rowIter = rowIndexNodeArray[i].next;
			SparseLinkNode<T1, T2>* needDelIter = NULL;
			while (NULL != rowIter)
			{
				needDelIter = rowIter;
				rowIter = rowIter->firstLevelNext;
				needDelIter->firstLevelNext = NULL;
				rowIndexNodeArray[i].next = rowIter;
			}
		}
	}

	for (int i = 0; i < SPARSE_TABLE_COL; i++)
	{
		if (NULL == colIndexNodeArray[i].next)
		{
			continue;
		}
		else
		{
			SparseLinkNode<T1, T2>* colIter = colIndexNodeArray[i].next;
			SparseLinkNode<T1, T2>* needDelIter = NULL;
			while (NULL != colIter)
			{
				needDelIter = colIter;
				colIter = colIter->secondLevelNext;
				needDelIter->secondLevelNext = NULL;
				delete needDelIter;
				needDelIter = NULL;
				colIndexNodeArray[i].next = colIter;
			}
		}
	}
}


template<class T1, class T2> 
bool SparseTable<T1, T2>::insert(const unsigned int firstIndex, const T1 firstData, const unsigned int secondIndex, const T2 secondData)
{
	bool rs = true;
	bool isOverFlow = isOverStack(firstIndex, secondIndex);
	if (!isOverFlow)
	{
		SparseLinkNode<T1, T2> *node = new SparseLinkNode<T1, T2>();
		node->firstDataIndex = firstIndex;
		node->firstData = firstData;
		node->secondDataIndex = secondIndex;
		node->secondData = secondData;
		node->firstLevelNext = NULL;
		node->secondLevelNext = NULL;
		rs = (insertAtRow(firstIndex, secondIndex, node) && insertAtCol(firstIndex, secondIndex, node));
	}
	else
	{
		rs = false;
	}

	return rs;
}


template<class T1, class T2>
bool SparseTable<T1, T2>::isOverStack(const unsigned int firstIndex, const unsigned int secondIndex)
{
	if ((firstIndex >= SPARSE_TABLE_ROW) || (secondIndex >= SPARSE_TABLE_COL))
	{
		return true;
	}
	return false;
}

template<class T1, class T2>
bool SparseTable<T1, T2>::insertAtRow(const unsigned int firstIndex, const unsigned int secondIndex, SparseLinkNode<T1, T2> *node)
{
	bool rs = false;
	SparseLinkNode<T1, T2> *iter = rowIndexNodeArray[firstIndex].next;

	if (NULL == iter)
	{
		//This row is empty, insert the node after head
		rowIndexNodeArray[firstIndex].next = node;
		rs = true;
	}
	else
	{
		SparseLinkNode<T1, T2> *preIter = NULL;
		while(NULL != iter)
		{
			unsigned int secondDataIndex = iter->secondDataIndex;
			if (secondIndex > secondDataIndex)
			{
				preIter = iter;
				iter = iter->firstLevelNext;
				continue;
			}
			else if (secondIndex == secondDataIndex)
			{
				//duplicate, error case
				rs = false;
				break;
			}
			else  //Need insert
			{
				
				if (NULL == preIter)
				{
					//At row level, insert the node after head and before iter
					node->firstLevelNext = iter;
					rowIndexNodeArray[firstIndex].next = node;
					rs = true;
					break;
				}
				else
				{
					//At row level, insert the node before iter and after preIter
					node->firstLevelNext = iter;
					preIter->firstLevelNext = node;
					rs = true;
					break;
				}
			}
		}

		if (!rs && (NULL == iter))
		{
			//At col level, insert the node after iter
			if (NULL == preIter)
			{
				//Impossible
				rs = false;
			}
			else
			{
				preIter->firstLevelNext = node;
				rs = true;
			}
		}
	}

	return rs;
}


template<class T1, class T2>
bool SparseTable<T1, T2>::insertAtCol(const unsigned int firstIndex, const unsigned int secondIndex, SparseLinkNode<T1, T2> *node)
{
	bool rs = false;
	SparseLinkNode<T1, T2> *iter = colIndexNodeArray[secondIndex].next;

	if (NULL == iter)
	{
		//This row is empty, insert the node after head
		colIndexNodeArray[secondIndex].next = node;
		rs = true;
	}
	else
	{
		SparseLinkNode<T1, T2> *preIter = NULL;
		while (NULL != iter)
		{
			unsigned int firstDataIndex = iter->firstDataIndex;
			if (firstIndex > firstDataIndex)
			{
				preIter = iter;
				iter = iter->secondLevelNext;
				continue;
			}
			else if (firstIndex == firstDataIndex)
			{
				//duplicate, error case
				rs = false;
				break;
			}
			else  //Need insert
			{
				if (NULL == preIter)
				{
					//At row level, insert the node after head and before iter
					node->secondLevelNext = iter;
					colIndexNodeArray[secondIndex].next = node;
					rs = true;
					break;
				}
				else
				{
					//At row level, insert the node before iter and after preIter
					node->secondLevelNext = iter;
					preIter->secondLevelNext = node;
					rs = true;
					break;
				}
			}
		}

		if (!rs && (NULL == iter))
		{
			//At col level, insert the node after iter
			if (NULL == preIter)
			{
				//Impossible
				rs = false;
			}
			else
			{
				preIter->secondLevelNext = node;
				rs = true;
			}
		}
	}
	return rs;
}

template<class T1, class T2>
bool SparseTable<T1, T2>::deleteViaIndex(const unsigned int firstIndex, const unsigned int secondIndex)
{
	bool rs = false;
	/******注意,使用模板时,变量名称不可与模板函数名称一致,
	原因仍在于模板在产生实例化时才会调用相关代码,若变量与函数同名,
	编译器无法区分******/
	bool isOverFlow = isOverStack(firstIndex, secondIndex);  
	if (!isOverFlow)
	{
		//The && priority is very important, follow the left -> right sequence
		rs = (delAtRow(firstIndex, secondIndex) && (delAtCol(firstIndex, secondIndex)));
	}
	else
	{
		rs = false;
	}
	return rs;
}

template <class T1, class T2>
bool SparseTable<T1, T2>::delAtRow(const unsigned int firstIndex, const unsigned int secondIndex)
{
	bool rs = false;
	SparseLinkNode<T1, T2> *iter = rowIndexNodeArray[firstIndex].next;
	if (NULL == iter)
	{
		rs = false;
	}
	else
	{
		SparseLinkNode<T1, T2> *preIter = NULL;
		while (NULL != iter)
		{
			unsigned int secondLevelIndex = iter->secondDataIndex;
			if (secondIndex > secondLevelIndex)
			{
				preIter = iter;
				iter = iter->firstLevelNext;
				continue;
			}
			else if (secondIndex == secondLevelIndex)  //Find the node, need delete
			{
				//Be careful, not call delete to release the memory here, because the col level handle will still need it 
				if (NULL == preIter)   //delete the first
				{
					rowIndexNodeArray[firstIndex].next = iter->firstLevelNext;
					iter->firstLevelNext = NULL;
					rs = true;
					break;
				}
				else
				{
					preIter->firstLevelNext = iter->firstLevelNext;
					iter->firstLevelNext = NULL;
					rs = true;
					break;
				}
			}
			else //Not find the node, break
			{
				rs = false;
				break;
			}
		}
	}
	return rs;
}

template <class T1, class T2>
bool SparseTable<T1, T2>::delAtCol(const unsigned int firstIndex, const unsigned int secondIndex)
{
	bool rs = false;
	SparseLinkNode<T1, T2> *iter = colIndexNodeArray[secondIndex].next;
	if (NULL == iter)
	{
		rs = false;
	}
	else
	{
		SparseLinkNode<T1, T2> *preIter = NULL;
		while (NULL != iter)
		{
			unsigned int firstLevelIndex = iter->firstDataIndex;
			if (firstIndex > firstLevelIndex)
			{
				preIter = iter;
				iter = iter->secondLevelNext;
				continue;
			}
			else if (firstIndex == firstLevelIndex)  //Find the node, need delete
			{
				//Be careful, need to release the memory here 
				if (NULL == preIter)   //delete the first
				{
					colIndexNodeArray[secondIndex].next = iter->secondLevelNext;
					iter->secondLevelNext = NULL;
					delete iter;
					iter = NULL;
					rs = true;
					break;
				}
				else
				{
					preIter->secondLevelNext = iter->secondLevelNext;
					iter->secondLevelNext = NULL;
					delete iter;
					iter = NULL;
					rs = true;
					break;
				}
			}
			else //Not find the node, break
			{
				rs = false;
				break;
			}
		}
	}
	return rs;
}