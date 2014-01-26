#include "hooke.h"

double supplyD = 31.7;
 double takeupD = 50.0;
 double takeupC;// = 3.1415926535 * takeupD;
 double supplyS = 83;
 double takeupS = 50;
 int supplyA = 100;
 int takeupA = 100;
 double transferLength = 1000; //mm
 int pulsesperrevolution = 50000;	//checkthis 
 
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

double GetsupplyC(void)
{
	return 3.1415926535 * supplyD;
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