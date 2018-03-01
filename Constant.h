#ifndef  _CONSTANT_H_
#define _CONSTANT_H_

#define NULL 0
#define RED 0
#define BLACK 1
const int QUEUE_SIZE = 100;
//const int QUEUE_DEFAULT_VALUE = -1;
enum QUEUE_PTR_FLAG{
	READ_PTR = 1,
	WRITE_PTR = 2
};

const int STACK_SIZE = 10;
const int STACK_DEFAULT_VALUE = -1;

const int SORT_ARRAY_SIZE = 64;

const int SEARCH_ARRAY_SIZE = 16;

const int BIN_TREE_NODE_SIZE = 16;

const int HEAP_NODE_SIZE = 16;

const int LINK_NODE_SIZE = 16;

const int SPARSE_TABLE_ROW = 4;
const int SPARSE_TABLE_COL = 8;



#endif // ! _CONSTANT_H_
