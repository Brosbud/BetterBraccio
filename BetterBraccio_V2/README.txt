
	
	Call library with; 

		- RobotMove <your variable name>; - 

	

	-setCenter(base, shoulder, elbow, wrist vertical, wrist rotation, gripper)- 
			Set your own calibrated center point, saved in ram, input degrees of rotation

	-getCenter(int)- fetch your own calibrated center point, by writing motor number;
			1 - Base
			2 - Shoulder
			3 - Elbow
			4 - Wrist_v
			5 - Wrist_r
			6 - Gripper

	-getCenter(String)- fetch your own calibrated center point, by writing motor name or id, typos are corrected for;
				Motor name is for example: base, Base, BASE
				Motor id is for example: m1, M2

	-moveCenter(speed)- Moves motors to your own calibrated center point;
				speed is 0-30 milliseconds between degrees of rotation, 0 is fastest, 30 is slowest 
	

	-softStart()- Customized softStart moves servos to default safe position
	-softStart(boolean)- softStart but boolean changes if pin 12, or servo voltage reference is written to 1 or 0;
				1 - motors can spin at full speed 	(true)
				0 - motors are shut down		(false)
	-softStart(motor1, motor2, motor3, motor4, motor5, motor6)-	
				softStart with your own customized safe position, input degrees of rotation
	
	
	-safePos(int speed) - Move to safePosition, either default or if softStart called with own locations	
	-safePos(int speed, boolean toggle) - False turns motors off after getting to safeposition
						Should be turned back on with softStart


	-servoMove(speed, motor1, motor2, motor3, motor4, motor5, motor6)- 
				Move the servos to location, input degrees of rotation, speed between 0 and 30, 0 fastest, 30 slowest

	-manualMove(speed)- communicate trought serial, speed sets speed for movements, 0 fastest, 30 slowest






