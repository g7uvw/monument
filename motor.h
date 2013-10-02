#pragma once
#include "serialib.h"
#include <string>
#include <iostream>
#include  <fstream>

class Motor
	{
	public:
		Motor(serialib *port, int portnum, char ID);
		//Motor( int portnum, char ID);
		virtual ~Motor(void);
		bool SetAcceleration(int Acceleration);
		bool SetHighResolution();
		bool EmergencyStop(void);
		bool SetSpeed(double Speed);
		bool SetDirection(bool Clockwise);
		double GetSpeed(void);

	public:
		int MotorID;
	protected:
		// Pointer to serial port
		serialib *m_pPort;
		int m_portnum;
	public:
		bool Lock(void);
		bool Free(void);
		bool Locked;
		std::string init1;
		std::string init2;
		std::string init3;
		int speed;

		void Demo(void);
		void Run(long int length, int acceleration, int speed);
		std::ofstream logfile;
		
	};

