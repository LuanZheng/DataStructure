#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <regex>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>
//#include "Queue.h"
//#include "Queue.cpp"
#include "Stack.h"
#include "Stack.cpp"
#include "Sort.h"
#include "Sort.cpp"
#include "Search.h"
#include "BinSeqTree.h"

//#include "Heap.h"
//#include "Heap.cpp"
#include "HashTable.h"
#include "LinkList.h"
#include "LinkList.cpp"
#include "SparseTable.h"
#include "SparseTable.cpp"
#include "CommonRegexMethod.h"
#include "BinSearchTree.h"
#include "BinSearchTree.cpp"
#include "RedBlackTree.h"
#include "RedBlackTree.cpp"
#include "HashFunction.h"
#include "RandomSelect.h"
#include "DataCompress.h"
#include "CombineCalculator.h"


#include "Test.h"

using namespace std;

template <typename T>
class PriorityQueueNode
{
public:
	unsigned int priority;
	T data;
};


void testLinkList()
{
	LinkList<int, LINK_NODE_SIZE> *linkList = new LinkList<int, LINK_NODE_SIZE>();
	linkList->insertFromHead(9);
	linkList->print();
	linkList->insertFromHead(7);
	linkList->print();
	linkList->insertAtLocation(8, 1);
	linkList->print();
	linkList->insertAtLocation(6, 8);
	linkList->print();
	linkList->insertAtLocation(5, 3);
	linkList->print();
	linkList->insertFromHead(4);
	linkList->print();
	linkList->insertFromHead(3);
	linkList->print();
	linkList->deleteFromHead();
	linkList->print();
	linkList->deleteViaData(7);
	linkList->print();
	linkList->deleteAtLocation(3);
	linkList->print();
	linkList->deleteAtLocation(14);
	linkList->print();
	linkList->deleteViaData(0);
	linkList->print();
	linkList->deleteViaData(1.2);
	linkList->print();
	delete linkList;
	linkList = NULL;
}

void testLinkList2()
{
	LinkList<string, LINK_NODE_SIZE> *linkList = new LinkList<string, LINK_NODE_SIZE>();
	linkList->insertFromHead("AA");
	linkList->print();
	linkList->insertFromHead("BB");
	linkList->print();
	linkList->insertAtLocation("CC", 1);
	linkList->print();
	linkList->insertAtLocation("DD", 8);
	linkList->print();
	linkList->insertAtLocation("EE", 3);
	linkList->print();
	linkList->insertFromHead("FF");
	linkList->print();
	linkList->insertFromHead("GG");
	linkList->print();
	linkList->deleteFromHead();
	linkList->print();
	linkList->deleteViaData("FF");
	linkList->print();
	linkList->deleteAtLocation(3);
	linkList->print();
	linkList->deleteAtLocation(14);
	linkList->print();
	linkList->deleteViaData("DDD");
	linkList->print();
	delete linkList;
	linkList = NULL;
}

void testHashTable()
{
	unsigned int oriArray[] = { 2, 3, 4, 5, 6, 7, 8, 1, 2, 3, 4, 5, 6, 7, 9, 5, 6, 25, 32, 12, 32, 45, 6 };
	HashTable hashTable;
	hashTable.saveIntoHashTable(oriArray, sizeof(oriArray) / sizeof(unsigned int));
	hashTable.print();
}

//void testPriorityQueue()
//{
//	LinkQueue<int> *firstQ = new LinkQueue<int>();
//	for (int i = 0; i < QUEUE_SIZE; i++)
//	{
//		LinkQueueNode<int>* linkQueueNode = new LinkQueueNode<int>();
//		linkQueueNode->data = i;
//		linkQueueNode->priority = i%8;
//		firstQ->enQueue(linkQueueNode);
//	}
//	for (int i = 0; i < QUEUE_SIZE; i++)
//	{
//		LinkQueueNode<int> *node = NULL;
//		firstQ->deQueue(node);
//		delete node;
//		node = NULL;
//	}
//}

void testQueue()
{
	ArrayQueue<int, QUEUE_SIZE> *firstQ = new ArrayQueue<int, QUEUE_SIZE>();
	for (int i = 0; i < 2 * QUEUE_SIZE; i++)
	{
		firstQ->enQueue(i);
	}
	int k = 6;
	for (int i = 0; i < 3 * QUEUE_SIZE; i++)
	{
		int value;
		firstQ->deQueue(value);
		value = 0;
	}
	k = 7;
	for (int i = 0; i < QUEUE_SIZE; i++)
	{
		firstQ->enQueue(i);
	}
	k = 8;
	for (int i = 0; i < QUEUE_SIZE; i++)
	{
		int value;
		firstQ->deQueue(value);
	}
	k = 9;
	delete firstQ;
	firstQ = NULL;
	k = 10;
}

void testLinkQueue()
{
	int loopTime = 0;
	while (loopTime < 1000)
	{
		loopTime++;
		LinkQueue<int, 100000> *linkQueue = new LinkQueue<int, 100000>();
		int data = -1;
		int i = 0;
		int totalBreak = 0;
		while (i < 100000)
		{
			//if (10 == totalBreak)
			//{
			//	break;
			//}
			linkQueue->enQueue(i);
			//cout << i << endl;
			i++;
			//_sleep(10000);
			//while (i > 10000)
			//{
			//	linkQueue->deQueue(data);
			//	if (linkQueue->isEmpty())
			//	{
			//		totalBreak++;
			//		i = 0;
			//		break;
			//	}
			//}
		}
		delete linkQueue;
		linkQueue = NULL;
	}
}

void testStack()
{
	Stack<int, LINK_NODE_SIZE> *stack = new Stack<int, LINK_NODE_SIZE>();
	for (int i = 0; i < 10; i++)
	{
		bool rs = stack->push(i);
		if (rs)
		{
			cout << "Push stack: value =" << i << endl;
		}
	}
	int data = -1;

	for (int i = 0; i < 3; i++)
	{
		bool rs = stack->topElem(data);
		if (rs)
		{
			cout << "Get Top stack: value =" << data << endl;
		}
	}

	for (int i = 0; i < 10; i++)
	{
		bool rs = stack->pop(data);
		if (rs)
		{
			cout << "Pop stack: value=" << data << endl;
			rs = stack->topElem(data);
			if (rs)
			{
				cout << "Get Top stack: value =" << data << endl;
			}
		}
	}
}


void testSort()
{
	unsigned int *pArray = new unsigned int[10000];
	srand(time(0));
	for (int i = 0; i < 10000; i++)
	{
		pArray[i] = rand();
	}

	Sort<unsigned int, 10000> sort;
	sort.print(pArray);
	sort.countSort(pArray);
	//sort.radixSort(pArray);
	//sort.print(pArray);
	//sort.mergeSort(pArray, 0, 99999);
	//sort.directInsertSort(pArray, 64);
	//sort.quickSort(0,99999,pArray);
	//sort.print(pArray);
	int i = 9;


	string *pStrArray = new string[8];
	pStrArray[0] = "abc";
	pStrArray[1] = "aaa";
	pStrArray[2] = "ccc";
	pStrArray[3] = "bc";
	pStrArray[4] = "ab";
	pStrArray[5] = "cda";
	pStrArray[6] = "ded";
	pStrArray[7] = "e";
	Sort<string, 8> sort2;
	sort2.print(pStrArray);
	sort2.mergeSort(pStrArray, 0, 7);
	sort2.print(pStrArray);
	int k = 9809;

	//Sort sort;
	//sort.print();
	//sort.directInsertSort();
	//sort.print();

	//Sort sort2;
	//sort2.print();
	//sort2.simpleSelectSort();
	//sort2.print();

	//Sort sort3;
	//sort3.print();
	//sort3.bubbleSort();
	//sort3.print();

	//Sort sort4;
	//sort4.print();
	//sort4.combSort();
	//sort4.print();

	//Sort sort5;
	//sort5.print();
	//sort5.shellSort();
	//sort5.print();


	//Sort sort6;
	//sort6.print();
	//sort6.quickSort(0, SORT_ARRAY_SIZE-1);
	//sort6.print();

	//Sort sort7;
	//sort7.print();
	//sort7.mergeSort(0, SORT_ARRAY_SIZE-1);
	//sort7.print();
	//int k = 9999;
}



void testSeqSerach()
{
	int a[SEARCH_ARRAY_SIZE];
	srand(time(0));
	for (int i = 0; i < SEARCH_ARRAY_SIZE; i++)
	{
		a[i] = rand();
	}

	int *p = a;

	Search search;
	for (int i = 0; i < 36767; i++)
	{
		bool result = search.seqSearch(p, SEARCH_ARRAY_SIZE, i);
		search.init();
		p = a;
	}
}

void testBinSerach()
{
	int a[SEARCH_ARRAY_SIZE];
	for (int i = 0; i < SEARCH_ARRAY_SIZE; i++)
	{
		a[i] = i;
	}

	int *p = a;

	Search search;
	for (int i = -1; i < 1025; i++)
	{
		search.binSearch(p, SEARCH_ARRAY_SIZE, i);
		search.init();
	}

}

void testBinTree()
{
	int a[BIN_TREE_NODE_SIZE];
	srand(time(0));
	for (int i = 0; i < BIN_TREE_NODE_SIZE; i++)
	{
		a[i] = rand();
	}
	BinSeqTree binSeqTree;
	for (int i = 0; i < BIN_TREE_NODE_SIZE; i++)
	{
		binSeqTree.insertNode(a[i]);
	}

	binSeqTree.midOrder();
	binSeqTree.preOrder();
	binSeqTree.lastOrder();
	binSeqTree.breadthFirstOrder();
}

void testDeleteNodeInBinTree()
{
	int a[BIN_TREE_NODE_SIZE] = { 6, 3, 2, 8, 54, 37, 21, 0, 65, 22, 74, 19, 86, 93, 33, 52 };
	BinSeqTree binSeqTree;
	for (int i = 0; i < BIN_TREE_NODE_SIZE; i++)
	{
		binSeqTree.insertNode(a[i]);
	}
	binSeqTree.midOrder();
	binSeqTree.preOrder();
	binSeqTree.lastOrder();
	binSeqTree.breadthFirstOrder();

	binSeqTree.deleteNode(6);
	binSeqTree.midOrder();
	binSeqTree.preOrder();
	binSeqTree.lastOrder();
	binSeqTree.breadthFirstOrder();

	binSeqTree.deleteNode(54);
	binSeqTree.midOrder();
	binSeqTree.preOrder();
	binSeqTree.lastOrder();
	binSeqTree.breadthFirstOrder();


	binSeqTree.deleteNode(93);
	binSeqTree.midOrder();
	binSeqTree.preOrder();
	binSeqTree.lastOrder();
	binSeqTree.breadthFirstOrder();


	binSeqTree.deleteNode(4);
	binSeqTree.midOrder();
	binSeqTree.preOrder();
	binSeqTree.lastOrder();
	binSeqTree.breadthFirstOrder();

	int k = 999;
}

void testDeleteNodeInBinTreeViaCopy()
{
	int a[BIN_TREE_NODE_SIZE] = { 6, 3, 2, 8, 54, 37, 21, 0, 65, 22, 74, 19, 86, 33, 52, 17 };
	BinSeqTree binSeqTree;
	for (int i = 0; i < BIN_TREE_NODE_SIZE; i++)
	{
		binSeqTree.insertNode(a[i]);
	}
	binSeqTree.midOrder();
	binSeqTree.preOrder();
	binSeqTree.lastOrder();
	binSeqTree.breadthFirstOrder();


	binSeqTree.deleteNodeViaCopy(54);
	binSeqTree.midOrder();
	binSeqTree.preOrder();
	binSeqTree.lastOrder();
	binSeqTree.breadthFirstOrder();

	binSeqTree.deleteNodeViaCopy(6);
	binSeqTree.midOrder();
	binSeqTree.preOrder();
	binSeqTree.lastOrder();
	binSeqTree.breadthFirstOrder();


	binSeqTree.deleteNodeViaCopy(21);
	binSeqTree.midOrder();
	binSeqTree.preOrder();
	binSeqTree.lastOrder();
	binSeqTree.breadthFirstOrder();
}

void testBalanceTree()
{
	int a[BIN_TREE_NODE_SIZE] = { 6, 3, 2, 8, 54, 37, 21, 0, 65, 22, 74, 19, 86, 33, 52, 17 };
	int *p = a;
	BinSeqTree binSeqTree;
	for (int i = 0; i < BIN_TREE_NODE_SIZE; i++)
	{
		binSeqTree.insertNode(a[i]);
	}
	binSeqTree.midOrder(p);
	p = a;

	binSeqTree.destoryTree();
	binSeqTree.balanceTree(p, 0, BIN_TREE_NODE_SIZE - 1);
}

void testDswBalance()
{
	int a[BIN_TREE_NODE_SIZE] = { 6, 3, 2, 8, 54, 37, 21, 0, 65, 22, 74, 19, 86, 33, 52, 17 };
	BinSeqTree binSeqTree;
	for (int i = 0; i < BIN_TREE_NODE_SIZE; i++)
	{
		binSeqTree.insertNode(a[i]);
	}
	binSeqTree.dswBalance(BIN_TREE_NODE_SIZE);
	int k = 999;
}

void testHeap()
{
	Heap<int, 100> heap;
	//int i = 9;
	//heap.AddElem(8);
	//heap.AddElem(9);
	int a[HEAP_NODE_SIZE] = { 6, 3, 2, 8, 54, 37, 21, 0, 65, 22, 74, 19, 86, 33, 52, 17 };
	//Heap heap;
	for (int i = 0; i < HEAP_NODE_SIZE; i++)
	{
		heap.AddElem(a[i]);
	}
	//int k = 888;
	for (int i = 0; i < HEAP_NODE_SIZE; i++)
	{
		int value;
		heap.deleteElem(value);
		cout << value << "    ";
	}
	int k = 99;
	//int kk = 999;

	//heap.AddElem(76);
	//heap.AddElem(54);
	//heap.AddElem(88);
	//heap.AddElem(62);
	//heap.AddElem(4);
	//heap.AddElem(2);
	//heap.AddElem(32);
	//heap.AddElem(22);
	//heap.AddElem(29);
	//int value;
	//cout << endl;
	//heap.deleteElem(value);
	//cout << value << "    ";
	//heap.deleteElem(value);
	//cout << value << "    ";
	//heap.deleteElem(value);
	//cout << value << "    ";
	//heap.AddElem(106);
	//heap.AddElem(1);
	//heap.deleteElem(value);
	//cout << value << "    ";
	//heap.deleteElem(value);
	//cout << value << "    ";
	//heap.deleteElem(value);
	//cout << value << "    ";
	//heap.deleteElem(value);
	//cout << value << "    ";
	//heap.deleteElem(value);
	//cout << value << "    ";
	//heap.deleteElem(value);
	//cout << value << "    ";
	//heap.deleteElem(value);
	//cout << value << "    ";
	//heap.deleteElem(value);
	//cout << value << "    ";
	//heap.deleteElem(value);
	//cout << value << "    ";
	//heap.deleteElem(value);
	//cout << value << "    ";
	//heap.deleteElem(value);
	//cout << value << "    ";
	//heap.deleteElem(value);
	//cout << value << "    ";
	//heap.deleteElem(value);
	//cout << value << "    ";
	//heap.deleteElem(value);
	//cout << value << "    ";
	//int kkk = 999;
}

void testRef(int &i)
{
	int k = i;
	i++;
	int j = 9;
}

void testRegex()
{
	ostringstream* buf = CommonRegexMethod::readFileIntoString("D:\Run through the rain.txt", 1);
	string inputStr = buf->str();
	RegexStudyTest::testMetaCharacter001(inputStr);
	if (NULL != buf)
	{
		delete buf;
		buf = NULL;
	}

	CommonRegexMethod::mobileMatchCheck("1232");
	CommonRegexMethod::mobileMatchCheck("这是什么情况");
	CommonRegexMethod::mobileMatchCheck("021-65643214");
	CommonRegexMethod::mobileMatchCheck("01234322456");
	CommonRegexMethod::mobileMatchCheck("13816657041");
	CommonRegexMethod::mobileMatchCheck("8613816657041");
	CommonRegexMethod::mobileMatchCheck("+8613816657041");
	CommonRegexMethod::mobileMatchCheck("(86)13716657041");
	CommonRegexMethod::mobileMatchCheck("(+86)13816657041");
	CommonRegexMethod::mobileMatchCheck("(+86)14916657041");
	CommonRegexMethod::mobileMatchCheck("(+86)12916657041");

	CommonRegexMethod::mobileMatchCheck("7613816657041");
	CommonRegexMethod::mobileMatchCheck("+7613816657041");
	CommonRegexMethod::mobileMatchCheck("(76)13816657041");
	CommonRegexMethod::mobileMatchCheck("(+76)13816657041");
	CommonRegexMethod::mobileMatchCheck("(+76)14916657041");
	CommonRegexMethod::mobileMatchCheck("(+76)12916657041");

	CommonRegexMethod::mobileMatchCheck("+813816657041");
	CommonRegexMethod::mobileMatchCheck("(8)13816657041");
	CommonRegexMethod::mobileMatchCheck("(+8)13816657041");
	CommonRegexMethod::mobileMatchCheck("(+8)14916657041");
	CommonRegexMethod::mobileMatchCheck("(+8)12916657041");

	CommonRegexMethod::idCardCheck("370105198202042530");
	CommonRegexMethod::idCardCheck("370181198205215309");
	CommonRegexMethod::idCardCheck("070105198202042530");
	CommonRegexMethod::idCardCheck("370181398205215309");
	CommonRegexMethod::idCardCheck("370105198222042530");
	CommonRegexMethod::idCardCheck("370105198202442530");
	CommonRegexMethod::idCardCheck("3701811982052153090");
	CommonRegexMethod::idCardCheck("17010519820204230");
	CommonRegexMethod::idCardCheck("370181198205215309X");
	CommonRegexMethod::idCardCheck("37018119820521530X");
	CommonRegexMethod::idCardCheck("37018119820521530x");

	CommonRegexMethod::emailCheck("jack.jack@163.com");
	CommonRegexMethod::emailCheck("123@456.com");
	CommonRegexMethod::emailCheck("_123@456.com");
	CommonRegexMethod::emailCheck("tiantian456.com");
	CommonRegexMethod::emailCheck("tiantian@456com");

	CommonRegexMethod::urlCheck("http://www.sina.com");
	CommonRegexMethod::urlCheck("https://www.sina.com");
	CommonRegexMethod::urlCheck("http://wwwm");
	CommonRegexMethod::urlCheck("http://wwwsina.com");
	CommonRegexMethod::urlCheck("wwwsina.com");
	CommonRegexMethod::urlCheck("www.sina.com");
	CommonRegexMethod::urlCheck("htp://www.sina.com");
	CommonRegexMethod::urlCheck("ht//www.sina.com");

	CommonRegexMethod::ipV4Check("255");
	CommonRegexMethod::ipV4Check("1");
	CommonRegexMethod::ipV4Check("61");
	CommonRegexMethod::ipV4Check("265");
	CommonRegexMethod::ipV4Check("355");
	CommonRegexMethod::ipV4Check("256");
	CommonRegexMethod::ipV4Check("0");
	CommonRegexMethod::ipV4Check("01");
	CommonRegexMethod::ipV4Check("255.");
	CommonRegexMethod::ipV4Check("1.");
	CommonRegexMethod::ipV4Check("61.");
	CommonRegexMethod::ipV4Check("265.");
	CommonRegexMethod::ipV4Check("355.");
	CommonRegexMethod::ipV4Check("256.");
	CommonRegexMethod::ipV4Check("0.");
	CommonRegexMethod::ipV4Check("01.");
	CommonRegexMethod::ipV4Check("255.255");
	CommonRegexMethod::ipV4Check("1.1");
	CommonRegexMethod::ipV4Check("61.61");
	CommonRegexMethod::ipV4Check("265.265");
	CommonRegexMethod::ipV4Check("355.355");
	CommonRegexMethod::ipV4Check("256.256");
	CommonRegexMethod::ipV4Check("0.0");
	CommonRegexMethod::ipV4Check("01.01");

	CommonRegexMethod::ipV4Check("255.255.255.0");
	CommonRegexMethod::ipV4Check("355.255.255.0");
	CommonRegexMethod::ipV4Check("55.255.255.0");
	CommonRegexMethod::ipV4Check("255.25.255.0");
	CommonRegexMethod::ipV4Check("0.255.255.0");
	CommonRegexMethod::ipV4Check(". . . .");
	CommonRegexMethod::ipV4Check("什么情况?");
	CommonRegexMethod::ipV4Check("255.2.5.255.0");
	CommonRegexMethod::ipV4Check("1.25.35.0");


	CommonRegexMethod::ipV6Check("ABCD:CDCD:FFEE:3232:EDED:FFFF:4353:1234");
	CommonRegexMethod::ipV6Check("ABCD:CDCD:FYEE:3232:EDED:FFFF:4353:1234");
	CommonRegexMethod::ipV6Check("8888::8:800:7777:4444");
	CommonRegexMethod::ipV6Check("::FFFF:129.24.6.7");
	CommonRegexMethod::ipV6Check("FEDC::7654:3210::BA98:7654:3210");
	CommonRegexMethod::ipV6Check("FEDC:BA98:7654:3210");
	CommonRegexMethod::ipV6Check("::");
	CommonRegexMethod::ipV6Check("什么情况?");
	CommonRegexMethod::ipV6Check("255.2.5.255.0");
	CommonRegexMethod::ipV6Check("1.25.35.0");

	CommonRegexMethod::creditCardCheck("4534343421211212");
	CommonRegexMethod::creditCardCheck("5534343421211212");
	CommonRegexMethod::creditCardCheck("8534343421211212");
	CommonRegexMethod::creditCardCheck("6234343421211212");
	CommonRegexMethod::creditCardCheck("343434342121112");
	CommonRegexMethod::creditCardCheck("453434342121112");
	CommonRegexMethod::creditCardCheck("55343434212311212");
	CommonRegexMethod::creditCardCheck("853434342211212");
	CommonRegexMethod::creditCardCheck("623433421211212");
	CommonRegexMethod::creditCardCheck("3434343421212112");

	CommonRegexMethod::passwordCheck("123456");
	CommonRegexMethod::passwordCheck("abcabc");
	CommonRegexMethod::passwordCheck("123456abc");
	CommonRegexMethod::passwordCheck("123456abcABC");
	CommonRegexMethod::passwordCheck("AAbb@@#$");
	CommonRegexMethod::passwordCheck("AA22@@#$");
	CommonRegexMethod::passwordCheck("11bb@@#$");
	CommonRegexMethod::passwordCheck("123456abcABC@");
	CommonRegexMethod::passwordCheck("!Qa1");
	CommonRegexMethod::passwordCheck("123456abcABC@123456abcABC@");

	string strArray[3] = {
		"上海浦东",
		"上海虹桥",
		"浦东机场"
	};

	CommonRegexMethod::vagueSearch(strArray, 3, "浦东");

	CommonRegexMethod::matchPriceInfo("E:\\南航.txt", "\\u00A5(\\s*)(\\d+)", 2);
}

void testPriorityQueue()
{
	PriorityLinkQueue<PriorityQueueNode<int>, 30000> *priorityLinkQueue = new PriorityLinkQueue<PriorityQueueNode<int>, 30000>();

	unsigned int num = 0;
	while (num < 2)
	{
		num++;
		cout << "NUM:" << num << endl;
		for (int i = 0; i < 40000; i++)
		{
			PriorityQueueNode<int> prioQueueNode;
			prioQueueNode.priority = (i % 5);
			prioQueueNode.data = i;

			priorityLinkQueue->enQueue(prioQueueNode);
		}

		_sleep(2000);

		for (int i = 0; i < 35000; i++)
		{
			PriorityQueueNode<int> deQueueNode;
			priorityLinkQueue->deQueue(deQueueNode);
		}

		_sleep(2000);
	}

	for (int i = 0; i < 40000; i++)
	{
		PriorityQueueNode<int> prioQueueNode;
		prioQueueNode.priority = (i % 5);
		prioQueueNode.data = i;

		priorityLinkQueue->enQueue(prioQueueNode);
	}

	delete priorityLinkQueue;
	priorityLinkQueue = NULL;
}




wstring readUniqudeFile(const char *fileName)
{
	wstring wStr;
	ifstream fin;
	fin.open(fileName, ios::binary);
	// 跳过unicode文本开头有两个字节0xFFFE（称作BOM，用于标识unicode编码）
	fin.seekg(2, ios::beg);
	while (!fin.eof())
	{
		wchar_t wch;
		fin.read((char *)(&wch), 2);
		wStr.append(1, wch);
	}
	return wStr;
}


std::wstring s2ws(const std::string& s)
{
	setlocale(LC_ALL, "chs");
	const char* _Source = s.c_str();
	size_t _Dsize = s.size() + 1;
	wchar_t *_Dest = new wchar_t[_Dsize];
	wmemset(_Dest, 0, _Dsize);
	mbstowcs(_Dest, _Source, _Dsize);
	std::wstring result = _Dest;
	delete[]_Dest;
	setlocale(LC_ALL, "C");
	return result;
}


std::string ws2s(const std::wstring& ws)
{
	std::string curLocale = setlocale(LC_ALL, NULL); // curLocale = "C";
	setlocale(LC_ALL, "chs");
	const wchar_t* _Source = ws.c_str();
	size_t _Dsize = 2 * ws.size() + 1;
	char *_Dest = new char[_Dsize];
	memset(_Dest, 0, _Dsize);
	wcstombs(_Dest, _Source, _Dsize);
	std::string result = _Dest;
	delete[]_Dest;
	setlocale(LC_ALL, curLocale.c_str());
	return result;
}

void testBinSearchTree()
{
	BinSearchTree<int, 200> binSearchTree;
	int a[200];
	srand(time(0));
	for (int i = 0; i < 200; i++)
	{
		a[i] = rand();
	}
	for (int i = 0; i < 200; i++)
	{
		binSearchTree.insert(a[i]);
	}
	//binSearchTree.insert(28248);
	//binSearchTree.insert(15998);
	//binSearchTree.insert(28891);
	//binSearchTree.insert(13315);
	//binSearchTree.insert(21444);
	//binSearchTree.insert(4358);
	//binSearchTree.insert(15132);
	//binSearchTree.insert(12538);
	binSearchTree.dswBalance();
	binSearchTree.scopeOrder();
	int i = 0;
}


void testBinSearchTree2()
{
	BinSearchTree<int, 9> binSearchTree;
	int a[9];
	binSearchTree.insert(8);
	binSearchTree.insert(4);
	binSearchTree.insert(12);
	binSearchTree.insert(2);
	binSearchTree.insert(6);
	binSearchTree.insert(1);
	binSearchTree.insert(9);
	binSearchTree.insert(7);
	binSearchTree.insert(3);

	binSearchTree.delViaCopy(6);

	binSearchTree.dswBalance();
	binSearchTree.scopeOrder();
	int i = 0;
}

void testAVLSearchTree()
{
	BinSearchTreeAVL<int, 100000>* binSearchTreeAVL = new BinSearchTreeAVL<int, 100000>();
	int a[100000];
	srand(time(0));
	for (int i = 0; i < 100000; i++)
	{
		a[i] = rand();
	}
	for (int i = 0; i < 100000; i++)
	{
		binSearchTreeAVL->insert(a[i]);
	}
	for (int i = 0; i < 99980; i++)
	{
		binSearchTreeAVL->delViaCopy(a[i]);
	}
	if (NULL != binSearchTreeAVL)
	{
		delete binSearchTreeAVL;
		binSearchTreeAVL = NULL;
	}
}

void testAVLSearchTree3()
{
	BinSearchTreeAVL<int, 32>* binSearchTreeAVL = new BinSearchTreeAVL<int, 32>();

	binSearchTreeAVL->insert(15841);
	binSearchTreeAVL->insert(5769);
	binSearchTreeAVL->insert(22445);
	binSearchTreeAVL->insert(3230);
	binSearchTreeAVL->insert(11768);
	binSearchTreeAVL->insert(19617);
	binSearchTreeAVL->insert(27316);
	binSearchTreeAVL->insert(2604);
	binSearchTreeAVL->insert(4159);
	binSearchTreeAVL->insert(9204);
	binSearchTreeAVL->insert(14362);
	binSearchTreeAVL->insert(17809);
	binSearchTreeAVL->insert(22024);
	binSearchTreeAVL->insert(25558);
	binSearchTreeAVL->insert(31522);
	binSearchTreeAVL->insert(2372);
	binSearchTreeAVL->insert(3077);
	binSearchTreeAVL->insert(4372);
	binSearchTreeAVL->insert(8024);
	binSearchTreeAVL->insert(10423);
	binSearchTreeAVL->insert(14251);
	binSearchTreeAVL->insert(15504);
	binSearchTreeAVL->insert(17563);
	binSearchTreeAVL->insert(19404);
	binSearchTreeAVL->insert(21983);
	binSearchTreeAVL->insert(22586);
	binSearchTreeAVL->insert(26758);
	binSearchTreeAVL->insert(7421);
	binSearchTreeAVL->insert(8860);
	binSearchTreeAVL->insert(9364);
	binSearchTreeAVL->insert(10503);
	binSearchTreeAVL->insert(15452);

	//binSearchTreeAVL->scopeOrder();

	binSearchTreeAVL->delViaCopy(15841);
	binSearchTreeAVL->delViaCopy(5769);
	binSearchTreeAVL->delViaCopy(22445);
	binSearchTreeAVL->delViaCopy(3230);
	binSearchTreeAVL->delViaCopy(11768);
	binSearchTreeAVL->delViaCopy(19617);
	binSearchTreeAVL->delViaCopy(27316);
	binSearchTreeAVL->delViaCopy(2604);
	binSearchTreeAVL->delViaCopy(4159);
	binSearchTreeAVL->delViaCopy(9204);
	binSearchTreeAVL->delViaCopy(14362);
	binSearchTreeAVL->delViaCopy(17809);
	binSearchTreeAVL->delViaCopy(22024);
	binSearchTreeAVL->delViaCopy(25558);
	binSearchTreeAVL->delViaCopy(31522);
	binSearchTreeAVL->delViaCopy(2372);
	binSearchTreeAVL->delViaCopy(3077);
	binSearchTreeAVL->delViaCopy(4372);
	binSearchTreeAVL->delViaCopy(8024);
	binSearchTreeAVL->delViaCopy(10423);
	//binSearchTreeAVL->scopeOrder();
	binSearchTreeAVL->delViaCopy(14251);
	binSearchTreeAVL->delViaCopy(15504);
	binSearchTreeAVL->delViaCopy(17563);
	binSearchTreeAVL->delViaCopy(19404);
	binSearchTreeAVL->delViaCopy(21983);
	binSearchTreeAVL->delViaCopy(22586);
	binSearchTreeAVL->delViaCopy(26758);
	binSearchTreeAVL->delViaCopy(7421);
	binSearchTreeAVL->delViaCopy(8860);
	binSearchTreeAVL->delViaCopy(9364);
	binSearchTreeAVL->delViaCopy(10503);
	binSearchTreeAVL->delViaCopy(15452);
}


void testAVLSearchTree2()
{
	BinSearchTree<int, 8>* binSearchTreeAVL = new BinSearchTreeAVL<int, 8>();
	binSearchTreeAVL->insert(16);
	binSearchTreeAVL->insert(8);
	binSearchTreeAVL->insert(24);
	binSearchTreeAVL->insert(4);
	binSearchTreeAVL->insert(12);
	binSearchTreeAVL->insert(19);
	binSearchTreeAVL->insert(10);
	binSearchTreeAVL->insert(14);
	binSearchTreeAVL->delViaCopy(19);
}

int add(int &a, int &b)
{
	a = 6;
	b = 5;
	return a + b;
}

//int add(int &a, int &b)
//{
//	a = 6;
//	b = 5;
//	return a + b;
//}


void main()
{
	//RedBlackTree rbTree;
	RedBlackTree<int, 64>* rbTree = new RedBlackTree<int, 64>();
	rbTree->insert(17);
	rbTree->insert(15);
	rbTree->insert(6);
	rbTree->insert(28);
	rbTree->insert(16);
	rbTree->insert(8);

	rbTree->rightRotate(15);
	rbTree->leftRotate(6);

	rbTree->rightRotate(17);
	rbTree->leftRotate(17);

	CombineCalculator cc;
	//auto now = std::chrono::system_clock::now();
	//auto ticks = std::chrono::system_clock::to_time_t(now);
	clock_t start, ends;
	start = clock();

	for (int i = 0; i < 10; i++)
	{
		cc.calculateCombine(20, 50);
	}
	ends = clock();
	//auto now2 = std::chrono::system_clock::now();
	//auto ticks2 = std::chrono::system_clock::to_time_t(now2);
	

	DataCompress dc;
	string strInput = "ACCGTAC$";
	int len = strInput.length();
	char *firstArray = new char[len + 1];
	char *lastArray = new char[len + 1];
	int *pOutLastIndexSeq = new int[len];
	memset(firstArray, 0, sizeof(char)*(len + 1));
	memset(lastArray, 0, sizeof(char)*(len + 1));
	memset(pOutLastIndexSeq, 0, sizeof(int)*len);
	dc.BWTEncodeing(firstArray, lastArray, pOutLastIndexSeq, strInput);
	cout << "FirstArray is:" << firstArray << endl;
	cout << "LastArray is:" << lastArray << endl;

	char *pOriginalArray = new char[len+1];
	memset(pOriginalArray, 0, sizeof(char)*(len+1));
	dc.BTWDecoding(firstArray, lastArray, pOriginalArray);

	
	for (int i = 0; i < len; i++)
	{
		cout << pOriginalArray[i] << endl;
	}

	if (firstArray != NULL)
	{
		delete[] firstArray;
		firstArray = NULL;
	}
	if (lastArray != NULL)
	{
		delete[] lastArray;
		lastArray = NULL;
	}
	if (pOutLastIndexSeq != NULL)
	{
		delete[] pOutLastIndexSeq;
		pOutLastIndexSeq = NULL;
	}
	if (pOriginalArray != NULL)
	{
		delete[] pOriginalArray;
		pOriginalArray = NULL;
	}

	int aa = 1, bb = 2;
	int c = add(aa, bb);

	int maxIndex, minIndex;
	int a[11] = { 3, 5, -12, 4, 0, 6, 5, 4, 1, 9, 17 };
	RandomSelect rs;
	rs.selectMaxAndMin(a, 11, maxIndex, minIndex);
	int valueIndex = rs.selectXthMinValue(a, 6, 11);
	if (valueIndex == -1)
	{
		return;
	}
	int valueXthMin = a[valueIndex];

	int valueIndex2 = rs.selectXthMaxValue(a, 6, 10);
	if (valueIndex2 == -1)
	{
		return;
	}
	int valueXthMax = a[valueIndex2];

	unsigned int value = HashFunction::divHashFunc(3721, 1000);
	unsigned int value2 = HashFunction::divHashFunc(7632, 1000);

	unsigned int value3 = HashFunction::overlapHashFunc(123456789, 1000);
	unsigned int value4 = HashFunction::overlapHashFunc(789456123, 1000);

	unsigned int value5 = HashFunction::squareMidHashFunc(3721, 1000);
	unsigned int value6 = HashFunction::squareMidHashFunc(7632, 1000);

	//testBinSearchTree();
	testAVLSearchTree();
	//testBinSearchTree2();
	//testAVLSearchTree2();
	//testAVLSearchTree3();
	int i = 0;

	Basic *basic = new Basic();
	basic->basicPrint1();
	basic->basicPrint2();
	basic->basicPrint2(22);

	Basic *derivedWithPolymeric = new Derived();
	derivedWithPolymeric->basicPrint1();           //For virtual func, it will go to the drived class
	derivedWithPolymeric->basicPrint2();           //For non virtual func, it still call the basic class
	derivedWithPolymeric->basicPrint2(33);

	Derived *derived = new Derived();
	derived->basicPrint1();
	derived->basicPrint2();   //Only could call the derived class basicPrint2, the basic class same name function is hide
	derived->basicPrint3();

	Basic basic2;
	Derived derived2;

	cout << "The size of basic is : " << sizeof(basic) << endl;
	cout << "The size of derivedWithPolymeric is: " << sizeof(derivedWithPolymeric) << endl;
	cout << "The size of derived is: " << sizeof(derived) << endl;
	cout << "The size of basic2 is :" << sizeof(basic2) << endl;
	cout << "The size of derived2 is :" << sizeof(derived2) << endl;

	int k = 888;

	return;
}