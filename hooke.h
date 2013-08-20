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

using namespace std;
int nRetCode = 0;
double supplyD = 30.0;
double takeupD = 50.2;
double takeupC = 3.1415926535 * takeupD;
int supplyS = 9000;
int takeupS = 8000;
int supplyA = 100;
int takeupA = 100;
long int transferLength = 1000; //mm
char tmp;
double temp;

#endif //HOOKE_H