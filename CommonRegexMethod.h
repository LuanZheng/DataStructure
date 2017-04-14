#ifndef _COMMON_REGEX_METHOD_H_
#define _COMMON_REGEX_METHOD_H_

#include <string>
#include <fstream>
#include <sstream>
using namespace std;

class RegexStudyTest
{
public:
	static bool testMetaCharacter001(string inputStr);
};

class CommonRegexMethod
{
public:
	static bool mobileMatchCheck(const string mobile);
	static bool idCardCheck(const string idCard);
	static bool emailCheck(const string email);
	static bool urlCheck(const string url);
	static bool ipV4Check(const string ipV4);
	static bool ipV6Check(const string ipV6);
	static bool creditCardCheck(const string creditCard);
	static bool passwordCheck(const string password);
	static void vagueSearch(const string* searchSpace, unsigned int searchSpaceLen, const string searchStr);
	static void matchPriceInfo(const char* fileName, const string pattern, const unsigned int numInPattern);
	static ostringstream* readFileIntoString(const char* fileName, const unsigned int fileFormat = 0);
private:	
	static bool convert(const char c, int &rs);
};

#endif // !_COMMON_REGEX_METHOD_H_

