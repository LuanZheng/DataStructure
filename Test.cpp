#include "Test.h"
#include <iostream>
using namespace std;

Basic::Basic()
{
	i = 1;
	k = 2;
}

void Basic::basicPrint1()
{
	cout << "This is the basic Print1 in basic class" << endl;
	cout << "I=" << i << "K=" << k << endl;
}

void Basic::basicPrint2()
{
	cout << "This is the basic Print2 in basic class" << endl;
	cout << "I=" << i << "K=" << k << endl;
}

void Basic::basicPrint3()
{
	cout << "This is the basic Print3 int the basic class" << endl;
	cout << "I=" << i << "K=" << k << endl;
}

void Basic::basicPrint2(int k)
{
	cout << "This is the overload basic Print2 in basic class, K=" << k << endl;
	cout << "I=" << i << "K=" << k << endl;
}

Derived::Derived()
{
	i = 3;
	k = 4;
}

void Derived::basicPrint1()
{
	cout << "This is the basic print1 in derived class, as it is virtual, it is polymorphic" << endl;
	cout << "I=" << i << "K=" << k << endl;
}

void Derived::basicPrint2()
{
	//Basic::basicPrint2(44);
	cout << "This is the basic print2 in derived class. It will hide (not overload) the 2 method in basic class with same name." << endl;
	cout << "I=" << i << "K=" << k << endl;
}
