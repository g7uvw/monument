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
	
	stringstream cmd;
	//cmd << "K37=30." << MotorID << CRLF; //set 50,000 counts and 10pps resolution
	cmd << "K37=100." << MotorID << CRLF; //Set 1:1 resolution with encoder
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
	//Speed vale here is in pulses
	//in 1:1 encoder mode, there are 50,000 pulses for one rev/sec
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


void Motor::Run(long int length, int acceleration, int speed, int direction)
	{
	//length is in pulse counts. In 1:1 encoder mode, 50k pulses is one revolution.
		
	stringstream cmd;
	cmd.str("");
	//speed *=10;	
	//stop the motor
	/*cmd << "]." << MotorID << CRLF;
	m_pPort->Write(cmd.str().c_str(),cmd.str().length());*/

	//tell the motor the current position is 0
	//all moves are relative from here
	cmd << "|2." << MotorID << CRLF;
	logfile << cmd.str() <<endl;
	m_pPort->Write(cmd.str().c_str(),cmd.str().length());

	//set speed and acceleration
	cmd << "A=" << acceleration << "." << MotorID << CRLF;
	logfile << cmd.str() <<endl;
	m_pPort->Write(cmd.str().c_str(),cmd.str().length());
	cmd << "S=" << speed << "." << MotorID << CRLF;
	logfile << cmd.str() <<endl;
	m_pPort->Write(cmd.str().c_str(),cmd.str().length());

	//set target position
	cmd << "P=" << direction*length << "." <<MotorID << CRLF;
	logfile << cmd.str() <<endl;
	m_pPort->Write(cmd.str().c_str(),cmd.str().length());

	//go
	cmd << "^." << MotorID << CRLF;
	logfile << cmd.str() <<endl;
	m_pPort->Write(cmd.str().c_str(),cmd.str().length());
	}


