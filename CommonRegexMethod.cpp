#include "CommonRegexMethod.h"
#include <regex>
#include <iostream>

bool CommonRegexMethod::mobileMatchCheck(const string mobile)
{
	//中国移动：
	//	139、138、137、136、135、134、159、158、157、150、151、152、147(数据卡)、188、187、182、183、184、178
	//	移动网络制式： 2G GSM；3G TD - SCDMA；4G TDD - LTE
	//	中国联通：
	//	130、131、132、156、155、186、185、145(数据卡)、176
	//	联通网络制式： 2G GSM；3G WCDMA；4G FDD - LTE和TDD - LTE
	//	中国电信：
	//	133、153、189、180、181、177、173(待放)
	//注意\可以用来分行,但千万不要加空格
//	string pattern{ "(([8][6])|([\+][8][6])|([\(][8][6][\)])|([\(][\+][8][6][\)]))?\
//1(([3][8])|([3][7])|([3][6])|([3][5])|([3][4])|([5][9])|([5][8])|([5][7])|([5][0])|\
//([5][1])|([5][2])|([4][7])|([8][8])|([8][7])|([8][2])|([8][3])|([8][4])|([7][8])|\
//([3][0])|([3][1])|([3][2])|([5][6])|([5][5])|([8][6])|([8][5])|([4][5])|([7][6])|\
//([3][3])|([5][3])|([8][9])|([8][0])|([8][1])|([7][7])|([7][3]))\\d{8}" };
	string pattern{ "((86)|(\\+86)|(\\(86\\))|(\\(\\+86\\)))?\
1((38)|(37)|(36)|(35)|(34)|(59)|(58)|(57)|(50)|\
(51)|(52)|(47)|(88)|(87)|(82)|(83)|(84)|(78)|\
(30)|(31)|(32)|(56)|(55)|(86)|(85)|(45)|(76)|\
(33)|(53)|(89)|(80)|(81)|(77)|(73))\\d{8}" };
	regex re(pattern);
	bool rs = regex_match(mobile, re);
	if (rs)
	{
		cout << mobile <<" is the valid mobile phone number in CMCC/CU/CT" << endl;
	}
	else
	{
		cout << mobile << " is the invalid mobile phone number in CMCC/CU/CT" << endl;
	}
	return rs;
}

bool CommonRegexMethod::idCardCheck(const string idCard)
{
	const unsigned int weightArray[17] = { 7, 9, 10, 5, 8, 4, 2, 1, 6, 3, 7, 9, 10, 5, 8, 4, 2 };
	const unsigned int crcFlagArray[11] = { 1, 0, 10, 9, 8, 7, 6, 5, 4, 3, 2 };
	bool rs = false;
	string pattern = {"[1-9]\\d{5}(([1][9])|([2][0]))\\d{2}(([0][1])|([0][2])|([0][3])|\
([0][4])|([0][5])|([0][6])|([0][7])|([0][8])|([0][9])|([1][0])|([1][1])|([1][2]))\
[0-3]\\d{4}(([0-9])|(X)|(x))"};
	regex re(pattern);
	rs = regex_match(idCard, re);
	if (rs)
	{
		int convertRs = -1;
		unsigned int sum = 0;
		for (int i = 0; i < 17; i++)
		{
			rs = convert(idCard[i], convertRs);
			if (rs && (-1 != convertRs))
			{
				sum += convertRs*weightArray[i];
			}
			else
			{
				rs = false;
				break;
			}
		}
		unsigned int index = sum % 11;
		rs = convert(idCard[17], convertRs);
		if (!rs)
		{
			cout << idCard << " is the invalid 2nd idCard in China" << endl;
		}
		else
		{
			if (convertRs == crcFlagArray[index])
				cout << idCard << " is the valid 2nd idCard in China" << endl;
			else
				cout << idCard << " is the invalid 2nd idCard in China" << endl;
		}
	}
	else
	{
		cout << idCard << " is the invalid 2nd idCard in China" << endl;
	}
	return rs;
}

bool CommonRegexMethod::emailCheck(const string email)
{
	bool rs = false;
	string pattern = { "\\w+([-+.]\\w+)*@\\w+([-.]\\w+)*\\.\\w+([-.]\\w+)*" };  //C++中,\符号需要转义,因此写作两个\\符号
	regex re(pattern);
	rs = regex_match(email, re);
	if (rs)
	{
		cout << email << " is the valid email address" << endl;
	}
	else
	{
		cout << email << " is the invalid email address" << endl;
	}
	return rs;
}

bool CommonRegexMethod::urlCheck(const string url)
{
	bool rs = false;
	string pattern = {"(([h][t][t][p][:][/][/])|([h][t][t][p][s][:][/][/]))?(\\w+)\\.((\\w+)|(.))*"};  //在中括号内[]的特殊字符,不用增加转义.[]中括号外的一定要增加\转义
	regex re(pattern);
	rs = regex_match(url, re);
	if (rs)
	{
		cout << url << " is the valid url address" << endl;
	}
	else
	{
		cout << url << " is the invalid url address" << endl;
	}
	return rs;
}

bool CommonRegexMethod::ipV4Check(const string ipV4)
{
	bool rs = false;
	string pattern = {"((([0-9])|([1-9]\\d{1})|([1]\\d{2})|([2][0-4]\\d{1})|([2][5][0-5]))\\.){3}\
(([0-9])|([1-9]\\d{1})|([1]\\d{2})|([2][0-4]\\d{1})|([2][5][0-5]))"};
	regex re(pattern);
	rs = regex_match(ipV4, re);
	if (rs)
	{
		cout << ipV4 << " is the valid ipv4 address" << endl;
	}
	else
	{
		cout << ipV4 << " is the invalid ipv4 address" << endl;
	}
	return rs;
}

bool CommonRegexMethod::ipV6Check(const string ipV6)
{
	bool rs = false;
	string pattern = {"((([0-9A-Fa-f]{1,4}:){7}[0-9A-Fa-f]{1,4})|\
(([0-9A-Fa-f]{1,4}:){6}:[0-9A-Fa-f]{1,4})|\
(([0-9A-Fa-f]{1,4}:){5}:([0-9A-Fa-f]{1,4}:)?[0-9A-Fa-f]{1,4})|\
(([0-9A-Fa-f]{1,4}:){4}:([0-9A-Fa-f]{1,4}:){0,2}[0-9A-Fa-f]{1,4})|\
(([0-9A-Fa-f]{1,4}:){3}:([0-9A-Fa-f]{1,4}:){0,3}[0-9A-Fa-f]{1,4})|\
(([0-9A-Fa-f]{1,4}:){2}:([0-9A-Fa-f]{1,4}:){0,4}[0-9A-Fa-f]{1,4})|\
(([0-9A-Fa-f]{1,4}:){6}((\\b((25[0-5])|(1\\d{2})|(2[0-4]\\d)|(\\d{1,2}))\b)\.){3}(\\b((25[0-5])|\
(1\\d{2})|(2[0-4]\\d)|(\\d{1,2}))\b))|\
(([0-9A-Fa-f]{1,4}:){0,5}:((\\b((25[0-5])|(1\\d{2})|(2[0-4]\\d)|(\\d{1,2}))\\b)\\.){3}(\\b((25[0-5])|\
(1\\d{2})|(2[0-4]\\d)|(\\d{1,2}))\\b))|\
(::([0-9A-Fa-f]{1,4}:){0,5}((\\b((25[0-5])|(1\\d{2})|(2[0-4]\\d)|(\\d{1,2}))\\b)\\.){3}(\\b((25[0-5])|\
(1\\d{2})|(2[0-4]\\d)|(\\d{1,2}))\\b))|\
([0-9A-Fa-f]{1,4}::([0-9A-Fa-f]{1,4}:){0,5}[0-9A-Fa-f]{1,4})|\
(::([0-9A-Fa-f]{1,4}:){0,6}[0-9A-Fa-f]{1,4})|(([0-9A-Fa-f]{1,4}:){1,7}:))"};
	regex re(pattern);
	rs = regex_match(ipV6, re);
	if (rs)
	{
		cout << ipV6 << " is the valid ipv6 address" << endl;
	}
	else
	{
		cout << ipV6 << " is the invalid ipv4 address" << endl;
	}
	return rs;
}

bool CommonRegexMethod::creditCardCheck(const string creditCard)
{
	bool rs = false;
	string pattern = {"((4\\d{3})|(5[1-5]\\d{2})|(6011)|(62\\d{2}))-?\\d{4}-?\\d{4}-?\\d{4}|3[4,7]\\d{13}"};
	regex re(pattern);
	rs = regex_match(creditCard, re);
	if (rs)
	{
		cout << creditCard << " is the valid creditCard address" << endl;
	}
	else
	{
		cout << creditCard << " is the invalid creditCard address" << endl;
	}
	return rs;
}

bool CommonRegexMethod::passwordCheck(const string password)
{
	bool rs = false;
	unsigned int len = password.length();
	if ((len >= 6) && (len <= 16))
	{
		string pattern1 = { "(.*)[A-Z](.*)" };
		string pattern2 = { "(.*)[a-z](.*)" };
		string pattern3 = { "(.*)[0-9](.*)" };
		string pattern4 = { "(.*)[^A-Za-z0-9](.*)" };
		regex re(pattern1);
		rs = regex_match(password, re);
		if (rs)
		{
			regex re(pattern2);
			rs = regex_match(password, re);
			if (rs)
			{
				regex re(pattern3);
				rs = regex_match(password, re);
				if (rs)
				{
					regex re(pattern4);
					rs = regex_match(password, re);
					if (rs)
					{
						rs = true;
						cout << "password valid!" << endl;
					}
					else
					{
						cout << "password invalid pattern4!" << endl;
					}
				}
				else
				{
					cout << "password invalid pattern3!" << endl;
				}
			}
			else
			{
				cout << "password invalid pattern2!" << endl;
			}
		}
		else
		{
			cout << "password invalid pattern1!" << endl;
		}
	}
	else
	{
		cout << "len invalid!" << endl;
	}

	return rs;
}

void CommonRegexMethod::vagueSearch(const string* searchSpace, unsigned int searchSpaceLen, const string searchStr)
{
	const string* oriPtr = searchSpace;
	bool rs = false;
	string prePattern = "(.*)" + searchStr + "(.*)";
	string pattern = { prePattern };
	regex re(pattern);
	for (unsigned int i = 0; i < searchSpaceLen; i++)
	{
		rs = regex_match(*searchSpace, re);
		if (rs)
		{
			cout << *searchSpace << " match the pattern:" << searchStr << endl;
		}
		searchSpace++;
	}
	searchSpace = oriPtr;
}

void CommonRegexMethod::matchPriceInfo(const char* fileName, const string pattern, const unsigned int numInPattern)
{
	ostringstream* buf = readFileIntoString(fileName);
	if (NULL != buf)
	{
		string result = buf->str();
		std::regex re(pattern);
		std::regex_iterator<std::string::iterator> rit(result.begin(), result.end(), re);
		std::regex_iterator<std::string::iterator> rend;

		while (rit != rend)
		{
			std::cmatch cm;
			regex_match(rit->str().c_str(), cm, re);
			for (int i = 0; i < cm.size(); i++)
			{
				std::cout << "CM:" << i << cm[i] << endl;
			}
			++rit;
		}
	}
	else
	{

	}
	delete buf;
	buf = NULL;
	return;
}


ostringstream* CommonRegexMethod::readFileIntoString(const char* filename, const unsigned int fileFormat)
{
	ifstream fin;
	ostringstream *buf = NULL;
	fin.open(filename, ios::binary);
	if (fin.is_open())
	{	
		buf = new ostringstream();
		while (!fin.eof())
		{
			if (0 == fileFormat)
			{
				wchar_t wch;
				fin.read((char *)(&wch), 2);
				buf->put(wch);
			}
			else
			{
				char ch;
				fin.read((char *)(&ch), 1);
				buf->put(ch);
			}
		}
	}
	return buf;
}



bool CommonRegexMethod::convert(const char c, int &rs)
{
	bool result = true;
	switch (c)
	{
	case '0':
		rs = 0;
		break;
	case '1':
		rs = 1;
		break;
	case '2':
		rs = 2;
		break;
	case '3':
		rs = 3;
		break;
	case '4':
		rs = 4;
		break;
	case '5':
		rs = 5;
		break;
	case '6':
		rs = 6;
		break;
	case '7':
		rs = 7;
		break;
	case '8':
		rs = 8;
		break;
	case '9':
		rs = 9;
		break;
	case 'x':
	case 'X':
		rs = 10;
		break;
	default:
		result = false;
		break;
	}
	return result;
}


bool RegexStudyTest::testMetaCharacter001(string inputStr)
{
	string pattern = { "(.*)\r\n" };
	std::regex re(pattern);
	std::regex_iterator<std::string::iterator> rit(inputStr.begin(), inputStr.end(), re);
	std::regex_iterator<std::string::iterator> rend;
	while (rit != rend)
	{
		std::cout << rit->str() << std::endl;
		++rit;
	}
	return true;
}