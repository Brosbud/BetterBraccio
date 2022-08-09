/*
	BetterBraccio is designed for the Braccio robot arm
*/

#include "BetterBraccio.h"
#include "Arduino.h"
#include "Servo.h"

Servo base;
Servo shoulder;
Servo elbow;
Servo wrist_v;
Servo wrist_r;
Servo gripper;

BetterBraccio::BetterBraccio()
{
	_Vref = 12;
	pinMode(_Vref, OUTPUT);
}

void BetterBraccio::setCenter(int M1, int M2, int M3, int M4, int M5, int M6)
{
	if(M1 > _M1min && M1 < _M1max) _M1center = M1;
	if(M2 > _M2min && M2 < _M2max) _M2center = M2;
	if(M3 > _M3min && M3 < _M3max) _M3center = M3;
	if(M4 > _M4min && M4 < _M4max) _M4center = M4;
	if(M5 > _M5min && M5 < _M5max) _M5center = M5;
	if(M6 > _M6min && M6 < _M6max) _M6center = M6;
}

/*
		Get Center of motor, if value is given as integer
*/


int BetterBraccio::getCenter(int motor)
{
	if(_M1center < 0){
		return -1;
	} else if (motor < 0 || motor > 6){
		return -1;
	}
	
	if(motor == 1) return _M1center;
	if(motor == 2) return _M2center;
	if(motor == 3) return _M3center;
	if(motor == 4) return _M4center;
	if(motor == 5) return _M5center;
	if(motor == 6) return _M6center;

	return -1;
}
	//---------------------------Get center of motor, if given as string

int BetterBraccio::getCenter(String motor)
{	
	if(_M1center < 0){
		return -1;
	}				
	if(motor.compareTo("base") == 0) return _M1center; 	// compare to regular
	if(motor.compareTo("shoulder") == 0) return _M2center;
	if(motor.compareTo("elbow") == 0) return _M3center;
	if(motor.compareTo("wrist_v") == 0) return _M4center;
	if(motor.compareTo("wrist_r") == 0) return _M5center;
	if(motor.compareTo("gripper") == 0) return _M6center;
	
	if(motor.compareTo("Base") == 0) return _M1center;		// compare to caps first
	if(motor.compareTo("Shoulder") == 0) return _M2center;
	if(motor.compareTo("Elbow") == 0) return _M3center;
	if(motor.compareTo("Wrist_v") == 0) return _M4center;
	if(motor.compareTo("Wrist_r") == 0) return _M5center;
	if(motor.compareTo("Gripper") == 0) return _M6center;
	
	if(motor.compareTo("BASE") == 0) return _M1center;		// compare to all caps
	if(motor.compareTo("SHOULDER") == 0) return _M2center;
	if(motor.compareTo("ELBOW") == 0) return _M3center;
	if(motor.compareTo("WRIST_V") == 0) return _M4center;
	if(motor.compareTo("WRIST_R") == 0) return _M5center;
	if(motor.compareTo("GRIPPER") == 0) return _M6center;

	
	if(motor.compareTo("wrist-v") == 0) return _M4center;	// compare wrist different possibilities
	if(motor.compareTo("wrist-r") == 0) return _M5center;
	if(motor.compareTo("Wrist-v") == 0) return _M4center;	
	if(motor.compareTo("Wrist-r") == 0) return _M5center;
	if(motor.compareTo("WRIST-V") == 0) return _M4center;	
	if(motor.compareTo("WRIST-R") == 0) return _M5center;

	
	if(motor.compareTo("M1") == 0) return _M1center;		// compare Motor call
	if(motor.compareTo("M2") == 0) return _M2center;
	if(motor.compareTo("M3") == 0) return _M3center;
	if(motor.compareTo("M4") == 0) return _M4center;
	if(motor.compareTo("M5") == 0) return _M5center;
	if(motor.compareTo("M6") == 0) return _M6center;
	
	if(motor.compareTo("m1") == 0) return _M1center;		// compare Motor call
	if(motor.compareTo("m2") == 0) return _M2center;
	if(motor.compareTo("m3") == 0) return _M3center;
	if(motor.compareTo("m4") == 0) return _M4center;
	if(motor.compareTo("m5") == 0) return _M5center;
	if(motor.compareTo("m6") == 0) return _M6center;

	return -1;
}

void BetterBraccio::moveCenter(int speed)
{
	if(!(_M1center < 0)){
	BetterBraccio::servoMove(speed, _M1center, _M2center, _M3center, _M4center, _M5center, _M6center);
	}
}
	


//--------------------------------------------------------------------------------------
void BetterBraccio::softStart()
{					// softStart default location
	if(_M1center > 0){
	_M1safe = _M1center;	//Set beginning locations if setCenter has been set
	_M5safe = _M5center;
	}
	
	_lastM1 = _M1safe;
	_lastM2 = _M2safe;
	_lastM3 = _M3safe;
	_lastM4 = _M4safe;
	_lastM5 = _M5safe;
	_lastM6 = _M6safe;
	
	//-----------------------
	shoulder.attach(10);		// Move cluster 1 
	elbow.attach(9);		// Shoulder + Elbow
	shoulder.write(_M2safe);
	elbow.write(_M3safe);
	digitalPWM(30, 2000, 0);
	//-----------------------
	base.attach(11);		//Move cluster 2
	wrist_v.attach(6);		// Base + Wrist + gripper
	wrist_r.attach(5);
	gripper.attach(3);
	base.write(_M1safe);	
	wrist_v.write(_M4safe);
	wrist_r.write(_M5safe);
	gripper.write(_M6safe);
	digitalPWM(15, 750, 1);
	//-----------------------
}

void BetterBraccio::softStart(boolean toggle)
{					// softStart default location
	if(_M1center > 0){
	_M1safe = _M1center;	//Set beginning locations if setCenter has been set
	_M5safe = _M5center;
	}
	
	_lastM1 = _M1safe;
	_lastM2 = _M2safe;
	_lastM3 = _M3safe;
	_lastM4 = _M4safe;
	_lastM5 = _M5safe;
	_lastM6 = _M6safe;
	
	//-----------------------
	shoulder.attach(10);		// Move cluster 1 
	elbow.attach(9);		// Shoulder + Elbow
	shoulder.write(_M2safe);
	elbow.write(_M3safe);
	digitalPWM(30, 2000, 0);
	//-----------------------
	base.attach(11);		//Move cluster 2
	wrist_v.attach(6);		// Base + Wrist + gripper
	wrist_r.attach(5);
	gripper.attach(3);
	base.write(_M1safe);	
	wrist_v.write(_M4safe);
	wrist_r.write(_M5safe);
	gripper.write(_M6safe);
	digitalPWM(15, 750, 0);
	//-----------------------
	if(toggle){
		digitalWrite(_Vref, 1);
	} else {
		digitalWrite(_Vref, 0);
	}
	
}

void BetterBraccio::softStart(int M1, int M2, int M3, int M4, int M5, int M6)
{
	
	if(M1 > _M1min && M1 < _M1max) _lastM1 = M1;	// check set values to mins and maxes
	if(M2 > _M2min && M2 < _M2max) _lastM2 = M2;
	if(M3 > _M3min && M3 < _M3max) _lastM3 = M3;
	if(M4 > _M4min && M4 < _M4max) _lastM4 = M4;
	if(M5 > _M5min && M5 < _M5max) _lastM5 = M5;
	if(M6 > _M6min && M6 < _M6max) _lastM6 = M6;
	
	_M1safe = M1;
	_M2safe = M2;
	_M3safe = M3;
	_M4safe = M4;
	_M5safe = M5;
	_M6safe = M6;
	
	_lastM1 = _M1safe;
	_lastM2 = _M2safe;
	_lastM3 = _M3safe;
	_lastM4 = _M4safe;
	_lastM5 = _M5safe;
	_lastM6 = _M6safe;
	
	shoulder.attach(10);		// Move cluster 1 
	elbow.attach(9);		// Shoulder + Elbow
	shoulder.write(_M2safe);
	elbow.write(_M3safe);
	digitalPWM(30, 2000, 0);

	base.attach(11);		//Move cluster 2
	wrist_v.attach(6);		// Base + Wrist + gripper
	wrist_r.attach(5);
	gripper.attach(3);
	
	base.write(_M1safe);	
	wrist_v.write(_M4safe);
	wrist_r.write(_M5safe);
	gripper.write(_M6safe);
	digitalPWM(15, 750, 1);
	
}

void BetterBraccio::safePos(int speed)
{
	
	BetterBraccio::servoMove(speed, _lastM1, _M2safe, _M3safe, _M4safe, _M5safe, _M6safe);
	BetterBraccio::servoMove(speed, _M1safe, _M2safe, _M3safe, _M4safe, _M5safe, _M6safe);
	
}

void BetterBraccio::safePos(int speed, boolean toggle)
{
	
	BetterBraccio::servoMove(speed, _lastM1, _M2safe, _M3safe, _M4safe, _M5safe, _M6safe);
	BetterBraccio::servoMove(speed, _M1safe, _M2safe, _M3safe, _M4safe, _M5safe, _M6safe);
	
	if(toggle == 0 || toggle == 1){
	delay(500);
	digitalWrite(_Vref, toggle);
	}
	
	
}

void BetterBraccio::setSafePos(int M1, int M2, int M3, int M4, int M5, int M6)
{
	
	_M1safe = M1;
	_M2safe = M2;
	_M3safe = M3;
	_M4safe = M4;
	_M5safe = M5;
	_M6safe = M6;
	
}

/*
	-------------------------------------------------------------------------------------------------------
						Generate PWM signal for Shield Voltage reference pin 12
	-------------------------------------------------------------------------------------------------------
*/
void BetterBraccio::digitalPWM(int dutyCycle, int milliSeconds, int toggle)
{
	_up = 80 + dutyCycle;
	_down = 450 - dutyCycle;

	_aika = milliSeconds * 2;
	_counter = 0;
	Serial.begin(9600);
	while(_counter < _aika)
	{
	_counter++;

	digitalWrite(_Vref, 1);
	delayMicroseconds(_up);
	digitalWrite(_Vref, 0);
	delayMicroseconds(_down);
	}
	digitalWrite(_Vref, toggle);
}

/*
	-------------------------------------------------------------------------------------------------------
						Allows synchonized servo movement
	-------------------------------------------------------------------------------------------------------
*/
void BetterBraccio::servoMove(int speed, int M1, int M2, int M3, int M4, int M5, int M6)
{
										
      if(speed > _speedmax) speed = _speedmax;//---------- SPEED
      if(speed < _speedmin) speed = _speedmin;
      if(M1 < _M1min) 	M1 = _M1min;	//---------- M1, BASE
      if(M1 > _M1max) 	M1 = _M1max;
      if(M2 < _M2min) 	M2 = _M2min;	//---------- M2, SHOULDER
      if(M2 > _M2max) 	M2 = _M2max;
      if(M3 < _M3min) 	M3 = _M3min;	//---------- M3, ELBOW
      if(M3 > _M3max) 	M3 = _M3max;
      if(M4 < _M4min) 	M4 = _M4min;	//---------- M4, WRIST VERTICAL
      if(M4 > _M4max) 	M4 = _M4max;
      if(M5 < _M5min) 	M5 = _M5min;	//---------- M5, WRIST ROTATION
      if(M5 > _M5max) 	M5 = _M5max;   	
      if(M6 < _M6min) 	M6 = _M6min;	//---------- M6, GRIPPER
      if(M6 > _M6max) 	M6 = _M6max;
      
		_exit = 1;		//--------- Set "Exit" status to 1, 0 breaks loop
	
      while(_exit == 1){

				delay(speed);  // Set step-delay
				
        if(M1 != _lastM1){	//----------------M1, BASE
        if(M1 > _lastM1){
            _lastM1++;
            base.write(_lastM1);
          }if(M1 < _lastM1){
            _lastM1--;
            base.write(_lastM1);
            }
		}
        if(M2 != _lastM2){	//----------------M2, SHOULDER
        if(M2 > _lastM2){
            _lastM2++;
            shoulder.write(_lastM2);
          }if(M2 < _lastM2){
            _lastM2--;
            shoulder.write(_lastM2);
            }
        }
        if(M3 != _lastM3){	//----------------M3, ELBOW
        if(M3 > _lastM3){
            _lastM3++;
            elbow.write(_lastM3);
          }if(M3 < _lastM3){
            _lastM3--;
            elbow.write(_lastM3);
            }
        }
        if(M4 != _lastM4){	//----------------M4, WRIST VERTICAL
        if(M4 > _lastM4){
            _lastM4++;
            wrist_v.write(_lastM4);
          }if(M4 < _lastM4){
            _lastM4--;
            wrist_v.write(_lastM4);
            }
        }
        if(M5 != _lastM5){	//----------------M5, WRIST ROTATION
        if(M5 > _lastM5){
            _lastM5++;
            wrist_r.write(_lastM5);
          }if(M5 < _lastM5){
            _lastM5--;
            wrist_r.write(_lastM5);
            }
        }
        if(M6 != _lastM6){	//----------------M6, GRIPPER
        if(M6 > _lastM6){
            _lastM6++;
            gripper.write(_lastM6);
          }if(M6 < _lastM6){
            _lastM6--;
            gripper.write(_lastM6);
            }
        }
        
        if( M1 == _lastM1 	//---------------- check if motors have reached end location
        &&  M2 == _lastM2
        &&  M3 == _lastM3
        &&  M4 == _lastM4
        &&  M5 == _lastM5
        &&  M6 == _lastM6
        ){
          _exit = 0;
          }else{
            _exit = 1;
            }
        }
}

/*
	-------------------------------------------------------------------------------------------------------
						Implements manual movement trough Serial monitor
	-------------------------------------------------------------------------------------------------------
*/
void BetterBraccio::manualMove(int speed)
{
	
while(true){
	
	Serial.end();														// If Serial port is already open, close it
	Serial.begin(_serSpeed);											// Begin serial communication at set speed (default 9600)
    
    Serial.println(F("Input motor you want to move"));						// Print instructions
    Serial.println(F("Input 'print', 'end', 'help' or motor number"));
    
  while(true){																//Begin first loop
    while (Serial.available()) {
    char c = Serial.read();  					//gets one byte from serial buffer
    _readString += c; 							//makes the String readString
    delay(2);  									//slow looping to allow buffer to fill with next character
	}
      
  if (_readString.length() >0) {	   			// if readString contains something
    Serial.println(F("Input;"));       			//Read back which motor to move
    Serial.println(_readString); 
    
    if(_readString.compareTo("print") == 10){		// if readString is print
		
	    Serial.println(F("			\n"
			"~~~~~					   \n"
			"    M1, M2, M3, M4, M5, M6	   "));
	    Serial.print(F("    [ "));
		Serial.print(_lastM1);
		Serial.print(F(", "));
		Serial.print(_lastM2);
		Serial.print(F(", "));
		Serial.print(_lastM3);
		Serial.print(F(", "));
		Serial.print(_lastM4);
		Serial.print(F(", "));
		Serial.print(_lastM5);
		Serial.print(F(", "));
		Serial.print(_lastM6);
		Serial.println(F(" ] "));
		Serial.println(F("~~~~~"));
		Serial.println();

            _motorStatus = 1;
            _readString = "";
	    break;
    } else if (_readString.compareTo("end") == 10){
		
		Serial.println(F("-------------MOVING TO SAFE POSITION-------------"));
		BetterBraccio::safePos(20, false);
		Serial.println(F("---------------------GOODBYE---------------------"));
		Serial.end();
		while(true){}

    }  else if (_readString.compareTo("help") == 10){
	
		Serial.println(F("--------------------HELP PAGE--------------------"));
		Serial.println(F("-----------------Serial Commands-----------------"));
		
		Serial.println(F("														\n "	
						"--~ | ----- | How to move? | ----- | ~-- 				\n " 
						"	Type the number of the motor (1 - 6) 				\n " 
						"	1 = Base,											\n "
						"	2 = Shoulder										\n " 
						"	3 = Elbow											\n " 
						"	4 = Wrist Vertical									\n " 
						"	5 = Wrist horizontal								\n " 
						"	6 = Gripper											\n " 
						"	Then enter the location you want,					\n " 
						"	in degrees of rotation, 							\n " 
						"	if field is entered empty, returns motors location	\n " 
						"														\n "
						"--~ | ----- | 'print' | ----- | ~--					\n "
						"      Prints all motor locations						\n "
						"      													\n "
						"--~ | ----- | 'end' | ----- | ~--						\n "
						"      Drives arm to safePos and ends transmission		\n "
						"      													\n "
						"      													\n "
						
						"----------------Movement Commands----------------									\n "
						"--~ | ----- | setCenter | ----- | ~--												\n "
						"    setCenter(motor 1, motor 2, motor 3, motor 4, motor 5, motor 6)				\n "
						"    	Set your own calibrated center point										\n "
						"      	----Not required----														\n "
						"       	But if you use it, the program will make use of it						\n "
						"        Motors given in degrees of rotation										\n "
						"      																				\n "
						"--~ | ----- | getCenter | ----- | ~--												\n "
						"    getCenter(motor)																\n "
						"        Returns center point as int												\n "	
						"        																			\n "
						"--~ | ----- | moveCenter | ----- | ~--												\n "
						"    moveCenter(int speed)															\n "
						"        Moves arm to center position with the given speed							\n "
						"        																			\n "
						"--~ | ----- | softStart | ----- | ~--												\n "
						"    softStart()																	\n "
						"        'Gently' moves arm to default position										\n "
						"    softStart(toggle)																\n "
						"        If toggle is false, pin 12 is LOW, and servos shut off						\n "
						"        If toggle is true, pin 12 is HIGH, and servos turn on						\n "
						"    sofStart(motor 1, motor 2, motor 3, motor 3, motor 5, motor 6)					\n "
						"        'Gently' moves arm to given position, motors given in degrees of rotation	\n "
						"        																			\n "
						"--~ | ----- | safePos | ----- | ~--    											\n "
						"    safePos(int speed)																\n "
						"        moves arm to default safe position, or if given, your safe position		\n "
						"	safePos(int speed, toggle)														\n "
						"        moves arm to default safe position, or if given, your safe position		\n "
						"        If toggle is false, pin 12 is LOW, and servos shut off						\n "
						"        If toggle is true, pin 12 is HIGH, and servos stay on						\n "
						"        																			\n "
						"--~ | ----- | servoMove | ----- | ~--												\n "
						"	servoMove(int speed, motor 1, motor 2, motor 3, motor 4, motor 5, motor 6)		\n "
						"        Moves servos to given position at given speed								\n "
						"        Motors given as degrees of rotation										\n "
						"        																			\n "
						"--~ | ----- | manualMove | ----- | ~--												\n "
						"   	manualMove(int speed)														\n "
						"        Allows manual movement of robot arm, trough serial monitor at given speed	\n "));
		_motorStatus = 1;
            	_readString = "";
	
    }  else {
     _motor = _readString.toInt();   	// convert String to motor int
     _readString = "";			// reset String
				
    if(_motor > 6 || _motor <= 0){			// if motor doesnt exist, throw error
        Serial.println(F("ERROR: INVALID MOTOR, try again"));
        break;
      }
     
      Serial.println(F("Input location in degrees of rotation"));	// ask input
    
      while(true){
        
        while (Serial.available()) {
          char c = Serial.read();  //gets one byte from serial buffer
          _readString += c; //makes the String readString
          delay(2);  //slow looping to allow buffer to fill with next character
        }
      
        if (_readString.length() >0) {
          Serial.println(F("Input;"));       //Read motor movement
          Serial.println(_readString);  
	  _location = _readString.toInt();  
	
	  if(_readString.compareTo("") == 10 || _readString.compareTo(" ") == 10){
		
		Serial.println();
		Serial.println(F("~~~~~"));
		Serial.println(F(" Last location; "));
	
		if(_motor == 1){ Serial.println(_lastM1); _location = _lastM1; }
		if(_motor == 2){ Serial.println(_lastM2); _location = _lastM2; }
		if(_motor == 3){ Serial.println(_lastM3); _location = _lastM3; }
		if(_motor == 4){ Serial.println(_lastM4); _location = _lastM4; }
		if(_motor == 5){ Serial.println(_lastM5); _location = _lastM5; }
		if(_motor == 6){ Serial.println(_lastM6); _location = _lastM6; }	
		
		Serial.println(F("~~~~~"));
		Serial.println();		
		}
	   
          _readString = "";
          _motorStatus = 1;
          break;
          }
        
      }
    }
  }
     if(_motorStatus == 1)break;		// Check if motors have been written to
  }
	
	_motorStatus = 0;	

    if(_motor == 1) BetterBraccio::servoMove(speed, _location, _lastM2, _lastM3, _lastM4, _lastM5, _lastM6);	// Move motors
    if(_motor == 2) BetterBraccio::servoMove(speed, _lastM1, _location, _lastM3, _lastM4, _lastM5, _lastM6);
    if(_motor == 3) BetterBraccio::servoMove(speed, _lastM1, _lastM2, _location, _lastM4, _lastM5, _lastM6);
    if(_motor == 4) BetterBraccio::servoMove(speed, _lastM1, _lastM2, _lastM3, _location, _lastM5, _lastM6);
    if(_motor == 5) BetterBraccio::servoMove(speed, _lastM1, _lastM2, _lastM3, _lastM4, _location, _lastM6);
    if(_motor == 6) BetterBraccio::servoMove(speed, _lastM1, _lastM2, _lastM3, _lastM4, _lastM5, _location);

	}
}










