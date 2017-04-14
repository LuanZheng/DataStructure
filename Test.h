#pragma once
class Basic
{
public:
	Basic();
	virtual void basicPrint1();
	void basicPrint2();
	void basicPrint2(int k);
	void basicPrint3();
protected:
	unsigned int i;
private:
	unsigned int k;
};

class Derived : public Basic
{
public:
	Derived();
	void basicPrint1();
	void basicPrint2();
private:
	unsigned int i;
	unsigned int k;
};

