#ifndef _HASH_FUNCTION_H_
#define _HASH_FUNCTION_H_

class HashFunction
{
public:
	static unsigned int divHashFunc(unsigned int keyValue, unsigned int length);
	static unsigned int overlapHashFunc(unsigned int keyValue, unsigned int length);
	static unsigned int squareMidHashFunc(unsigned int keyValue, unsigned int length);
	//static unsigned int selectHashFunc(unsigned int keyValue, unsigned int length);
private:
	static unsigned int findMaxPrime(unsigned int length);
};

#endif