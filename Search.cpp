#include "Search.h"
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include "Constant.h"

using namespace std;

Search::Search()
{
	searchTimes = 0;
}

bool Search::seqSearch(int *p, int length, int searchValue)
{
	for (int i = 0; i < length; i++)
	{
		searchTimes++;
		if (*p == searchValue)
		{
			print(searchValue, true);
			return true;
		}
		else
		{
			p++;
		}
	}
	print(searchValue, false);
	return false;
}


//bin search
//1. origin array should already in sequence
//2. Compare times will different as search value different, O(log(n))

bool Search::binSearch(int *p, int length, int searchValue)
{
	int beginFlag = 0;
	int endFlag = length-1;
	while (beginFlag <= endFlag)
	{
		searchTimes++;
		int compareFlag = (beginFlag + endFlag) / 2;
		if (*(p + compareFlag) < searchValue)
		{
			beginFlag = compareFlag + 1;
		}
		else if (*(p + compareFlag) > searchValue)
		{
			endFlag = compareFlag - 1;
		}
		else
		{
			print(searchValue, true);
			return true;
		}
	}
	print(searchValue, false);
	return false;
}

void Search::init()
{
	searchTimes = 0;
}

void Search::print(int value, bool flag)
{
	if (flag)
		cout << "SearchTimes:" << searchTimes << "Find value:" << value << endl;
	else
		cout << "SearchTimes:" << searchTimes << "Not find value:" << value << endl;
}