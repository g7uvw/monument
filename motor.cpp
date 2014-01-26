#include "motor.h"
#include <sstream>
#include <string.h>
#include <cmath>

#define CRLF "\x0D\x0A"

using namespace std;
//ofstream logfile;

Motor::Motor(serialib *port, int portnum, char ID)
//Motor::Motor(int portnum, char ID)
	: m_pPort(port)
	, m_portnum(portnum)
	, MotorID(ID)
	{
	logfile.open("log.txt",ios::out|ios::app);
	logfile <<"wibble"<<endl;
	
	char sRxBuf[300]={};
	stringstream cmd;
	cmd << "K37." << MotorID << CRLF;
	m_pPort->Write(cmd.str().c_str(),cmd.str().length());
	m_pPort->Read(sRxBuf,20,200);


	//cmd.clear();
	cmd.str("");
	cmd << "K14." << MotorID << "\x0D\x0A";
	m_pPort->Write(cmd.str().c_str(),cmd.str().length());
	m_pPort->Read(sRxBuf,200,2000);


	//dump motor params for debugging.
	cmd.str("");
	cmd << "%100" << CRLF;
	m_pPort->Write(cmd.str().c_str(),cmd.str().length());
	m_pPort->Read(sRxBuf,200,2000);
	init3 = sRxBuf;
	
	}


Motor::~Motor(void)
	{
		logfile.close();
	}

bool Motor::SetHighResolution()
	{
	//set 50,000 counts and 10pps resolution
	stringstream cmd;
	cmd << "K37=30." << MotorID << CRLF;
	m_pPort->Write(cmd.str().c_str(),cmd.str().length());
	return false;
	}

bool Motor::SetAcceleration(int Acceleration)
	{
	stringstream cmd;
	cmd << "A="<<Acceleration<<"." << MotorID;
	m_pPort->Write(cmd.str().c_str(),cmd.str().length());
	return false;
	}



bool Motor::SetSpeed(double Speed)
	{
	//speed passed here is in revs/sec
	//and use equation from datasheet.
	//double st = Speed*50000/10;
	Speed *= 100;		//speed is passed in mm/s
	speed = (int) round (Speed);
	stringstream cmd;
	cmd << "S="<<speed<<"." << MotorID << CRLF;
	logfile << cmd.str() <<endl;
	//logfile <<"setting speed" <<endl;
	m_pPort->Write(cmd.str().c_str(),cmd.str().length());
	return false;
	}
	
double Motor::GetSpeed(void)
	{
		//returns revs /sec
		return (double) speed;
	}


bool Motor::SetDirection(bool Clockwise)
	{
	unsigned long len;
	m_pPort->WriteString("GPS123");
	//CSerialPort::Write("GPS123",6);
	//sp.WritePort("GPS123",100,len);
	return false;
	}

bool Motor::EmergencyStop(void)
	{
	stringstream cmd;
	cmd << "]." << MotorID << CRLF;
	m_pPort->Write(cmd.str().c_str(),cmd.str().length());
	return false;
	}

bool Motor::Lock(void)
	{
	stringstream cmd;
	cmd << "(." << MotorID << CRLF;
	m_pPort->Write(cmd.str().c_str(),cmd.str().length());

	Locked = true;
	return false;
	}


bool Motor::Free(void)
	{
	stringstream cmd;
	cmd.str("");
	cmd << ")." << MotorID << CRLF;
	m_pPort->Write(cmd.str().c_str(),cmd.str().length());
	/*m_pPort->Write(cmd.str().c_str(),cmd.str().length());
	m_pPort->Write(cmd.str().c_str(),cmd.str().length());*/
	Locked = false; 
	return false;
	}


void Motor::Demo(void)
	{
	stringstream cmd;
	cmd.str("");
	cmd << "]." << MotorID << CRLF;
	m_pPort->Write(cmd.str().c_str(),cmd.str().length());
	cmd << "P." << MotorID << "=1000000000" << CRLF;
	m_pPort->Write(cmd.str().c_str(),cmd.str().length());
	cmd << "S." << MotorID << "=0" << CRLF;
	m_pPort->Write(cmd.str().c_str(),cmd.str().length());
	cmd << "A." << MotorID << "=100" << CRLF;
	m_pPort->Write(cmd.str().c_str(),cmd.str().length());
	//Sleep(100);
	cmd << "S." << MotorID << "=72" << CRLF;
	m_pPort->Write(cmd.str().c_str(),cmd.str().length());
	cmd << "^." << MotorID << CRLF;
	m_pPort->Write(cmd.str().c_str(),cmd.str().length());
	//Sleep(5000);
	cmd << "S." << MotorID << "=8000" << CRLF;
	m_pPort->Write(cmd.str().c_str(),cmd.str().length());
	cmd << "^." << MotorID << CRLF;
	m_pPort->Write(cmd.str().c_str(),cmd.str().length());
	//Sleep(5000);
	cmd << "S." << MotorID << "=100" << CRLF;
	m_pPort->Write(cmd.str().c_str(),cmd.str().length());
	cmd << "^." << MotorID << CRLF;
	m_pPort->Write(cmd.str().c_str(),cmd.str().length());
	//Sleep(5000);
	cmd << "S." << MotorID << "=-2000" << CRLF;
	m_pPort->Write(cmd.str().c_str(),cmd.str().length());
	cmd << "^." << MotorID << CRLF;
	m_pPort->Write(cmd.str().c_str(),cmd.str().length());
	//Sleep(5000);
	cmd << "]." << MotorID << CRLF;
	m_pPort->Write(cmd.str().c_str(),cmd.str().length());
	}


void Motor::Run(long int length, int acceleration, int speed)
	{
	stringstream cmd;
	cmd.str("");
	length *= 1000;	
	speed *=10;	
	//stop the motor
	/*cmd << "]." << MotorID << CRLF;
	m_pPort->Write(cmd.str().c_str(),cmd.str().length());*/

	//tell the motor the current position is 0
	//all moves are relative from here
	cmd << "|2." << MotorID << CRLF;
	m_pPort->Write(cmd.str().c_str(),cmd.str().length());

	//set speed and acceleration
	cmd << "A=" << acceleration << "." << MotorID << CRLF;
	m_pPort->Write(cmd.str().c_str(),cmd.str().length());
	cmd << "S=" << speed << "." << MotorID << CRLF;
	m_pPort->Write(cmd.str().c_str(),cmd.str().length());

	//set target position
	cmd << "P=" << -1*length << "." <<MotorID << CRLF;
	m_pPort->Write(cmd.str().c_str(),cmd.str().length());

	//go
	cmd << "^." << MotorID << CRLF;
	m_pPort->Write(cmd.str().c_str(),cmd.str().length());
	}


