/*
	BetterBraccio is designed for the Braccio robot arm
*/

#ifndef BetterBraccio_h
#define BetterBraccio_h

#include "Arduino.h"


class BetterBraccio
{
	public:
	BetterBraccio();		// initializes BetterBraccio, pin means the Vref pin on shield, -12-
	void setCenter(int M1,
			int M2, 
			int M3, 
			int M4, 
			int M5, 
			int M6
			);	 // void setCenter, set your own calibrated centerpoint, combines with getCenter and moveCenter
					
	int getCenter(int motor); 	// gets motor center location
	int getCenter(String motor); 	// String counterpart for previous method
	void moveCenter(int speed);  	// moves motors to given center positions, if center positions have not been set, skip
	

	void softStart();
	void softStart(boolean toggle);
	void softStart(int M1, 
			int M2, 
			int M3, 
			int M4, 
			int M5, 
			int M6
			);

	void safePos(int speed);
	void safePos(int speed, boolean toggle);
	void setSafePos(int M1, 
			int M2, 
			int M3, 
			int M4, 
			int M5, 
			int M6
			);
	
	void servoMove(int speed, 
			int M1, 
			int M2, 
			int M3, 
			int M4, 
			int M5, 
			int M6
			);
	void manualMove(int speed);
	
	private:
	// ---------------------- Initialize digitalPWM method
	void digitalPWM(int dutyCycle, int milliSeconds, int toggle);
	
	// ---------------------- Initialize last locations for servo move
	int _lastM1;
	int _lastM2;
	int _lastM3;
	int _lastM4;
	int _lastM5;
	int _lastM6;
	// ---------------------- Set start values for centerpoints, int version of null
	int _M1center = -1;
	int _M2center = -1;
	int _M3center = -1;
	int _M4center = -1;
	int _M5center = -1;
	int _M6center = -1;
	// ---------------------- Set safePos default values
	int _M1safe = 0;
	int _M2safe = 20;
	int _M3safe = 40;
	int _M4safe = 0;
	int _M5safe = 0;
	int _M6safe = 0;
	// ---------------------- Set max values for movement;
	int _M1max = 180;
	int _M2max = 160;
	int _M3max = 180;
	int _M4max = 180;
	int _M5max = 180;
	int _M6max = 70;
	int _speedmax = 30;
	// ---------------------- Set min values for movement;
	int _M1min = 0;
	int _M2min = 25;
	int _M3min = 0;
	int _M4min = 0;
	int _M5min = 0;
	int _M6min = 0;
	int _speedmin = 0;
	// ---------------------- 
	
	int _Vref;
	int _up;
	int _down;
	int _aika;
	int _counter;
	int _exit = 1;
	int _location = 90;
	int _motor = 0;
	int _motorStatus = 0;
		int _serSpeed = 9600; // change if serial doesn't work
	String _readString = "";
	String lastpos = "";
};	
	



#endif