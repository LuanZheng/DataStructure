#ifndef _DATA_COMPRESS_H_
#define _DATA_COMPRESS_H_
#include <string>
using namespace std;

class DataCompress
{
public:
	DataCompress();
	~DataCompress();
	bool BWTEncodeing(char* pOutFirstArray, char* pOutLastArray, int* pOutLastIndexSeq, const string &strInput);
	bool BTWDecoding(char* pInFirstArray, char* pInLastArray, char* pOutOriginalArray);
private:
	string cyclicShift(const string &strInput, int n);
	void calculatePreSum(int *pOutPreSum, const char *pInLastArray, int len);
	void calculateFirstIndex(char *pInFirstArray, int *pOutFirstIndex, int len);
	void getLastSeq(char* pInLastArray, int *pInCheckPreSum, int *pInPreSumIndex, int *pInOutLastIndexSeq, int len);
};

#endif