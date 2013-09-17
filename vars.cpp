#include "hooke.h"

double supplyD = 30.0;
 double takeupD = 50.2;
 double takeupC;// = 3.1415926535 * takeupD;
 double supplyS = 9000;
 double takeupS = 8000;
 int supplyA = 100;
 int takeupA = 100;
 double transferLength = 1000; //mm
 
void SetsupplyD (double val)
{
	supplyD = val;	
}

double GetsupplyD(void)
{
	return supplyD;
}

void SettakeupD (double val)
{
	takeupD = val;
}

double GettakeupD(void)
{
	return takeupD;
}

double GettakeupC(void)
{
	return 3.1415926535 * takeupD;
}

void SetsupplyS(double val)
{
	supplyS = val;
}

double GetsupplyS(void)
{
	return supplyS;
}

void SettakeupS(double val)
{
	takeupS = val;
}

double GettakeupS(void)
{
	return takeupS;
}

int GettakeupA(void)
{
	return takeupA;
}

int GetsupplyA(void)
{
	return takeupA;
}

void SettransferLength(double val)
{
	transferLength = val;
}

double GettransferLength(void)
{
	return transferLength;
}