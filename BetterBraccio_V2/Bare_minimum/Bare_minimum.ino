#include <BetterBraccio.h>

BetterBraccio robot;  // creates robot object from RobotMove library


void setup() {
  
  robot.softStart();  // "softly" drives motors to safePosition
  robot.manualMove(15); // get full updated documentation with "help"
  
}

void loop() {

}
