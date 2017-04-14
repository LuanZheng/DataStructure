#ifndef _SEARCH_H_
#define _SERACH_H_

class Search
{
public:
	Search();
	bool seqSearch(int *p, int length, int searchValue);
	bool binSearch(int *p, int length, int searchValue);
	void init();
private:
	void print(int value, bool flag);
	int searchTimes;
};


#endif // !_SEARCH_H_

