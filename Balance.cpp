#include "Arduino.h"
#include "Balance.h"
#include "ax12.h"
//dynamexl includes need to be written in here
//Test cmo

Balance::Balance(double pInit, double iInit, double dInit, int desiredVal) {
  //initialize the object
  //tuningValues
  pVal = pInit;
  iVal = iInit;
  dVal = pInit;
  //time
  timeInstance = 0;
  //error
  error = 0;
  errorSum = 0;
  //value
  setpoint = desiredVal;
};

/*changes*
1.Change PID values to doubles
2.change time so it is in seconds instead of milliseconds
3.after these two make sure data types agree

*/
int Balance::UpdatePID(int sensorVal) { //time is in millis, need to change so it is float/double in seconds
  //stuff that gets looped
  int previousTime = timeInstance;
  int previousError = error;
  error = setpoint - sensorVal;
  timeInstance = millis();
  int ellapsedTime = int(timeInstance - previousTime);   //(change of time)
  int errorChange = error - previousError;          //(change in error)
  //proportional term
  outVal = pVal * error;
  //integral term
  errorSum += ellapsedTime * error;
  outVal += errorSum * iVal;
  //derivative term
  if (ellapsedTime != 0 && previousError != 0) {
    int derivE = errorChange / ellapsedTime;
    outVal += derivE * dVal;
  }
  return outVal;
};

void Balance::SetPID(int pSet, int iSet, int dSet){
  pVal = pSet;
  iVal = iSet;
  dVal = dSet;
};

void Balance::SetDesiredVal(int desiredVal){
  setpoint = desiredVal;
};

//function that is called to initialize all the dynamexl motors
void Balance::ServosInitialize(){

};

//function that allows all motor positions (not wheel motors) to a specific orientation
void Balance::SetFrame(){
  // Standing - Set all 16 joint servos to center position
  // 0 -> 0 degrees, 512 -> 150 degree, 1023 -> 300 degree (max)
  int numServos = 16;             // 16 total joint servos
  for(int i = 0; i < numServos; i+2) {
    dxlSetGoalPosition(i, 512);   // 512 -> 150 degree, center position
    dxlSetGoalPosition(i+1, 512); // Move 2 at once
    delay(20);                    // Wait for servos to move
  }
};

//sets the speed of the two motors attached to the wheels
void Balance::SetSpeeds(){

};
