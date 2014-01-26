#pragma once
#ifndef HOOKE_H
#define HOOKE_H
//hooke.h

#include <menu.h>
#include <stdlib.h>
#include <iostream>
#include "motor.h"


#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
#define CTRLD 	4

#define         DEVICE_PORT             "/dev/ttyS0"                         // ttyS0 for linux

int realmain(Motor *Source, Motor *Sink);
//int setup_menu(void);
//int jog_menu(void);

void dosetup(Motor *Source, Motor *Sink);
void dojog(Motor *Source, Motor *Sink);
void dorun(Motor *Source, Motor *Sink);


void main_menu(Motor *Source, Motor *Sink);
int setup_menu(Motor *Source, Motor *Sink);
int jog_menu(Motor *Source, Motor *Sink);
//void runtime_menu(void);

void SetsupplyD (double val);
double GetsupplyD(void);
void SettakeupD (double val);
double GettakeupD(void);
double GettakeupC(void);
double GetsupplyC(void);
void SetsupplyS(double val);
double GetsupplyS(void);
void SettakeupS(double val);
double GettakeupS(void);
int GettakeupA(void);
int GetsupplyA(void);
void SettransferLength(double val);
double GettransferLength(void);

using namespace std;
//extern int nRetCode = 0;
//extern double supplyD = 30.0;
//extern double takeupD = 50.2;
//extern double takeupC = 3.1415926535 * takeupD;
//extern int supplyS = 9000;
//extern int takeupS = 8000;
//extern int supplyA = 100;
//extern int takeupA = 100;
//extern long int transferLength = 1000; //mm
//extern char tmp;
//extern double temp;

#endif //HOOKE_H