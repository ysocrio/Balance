#include "Arduino.h"
#include "Balance.h"
#include "ax12.h"
//dynamexl includes need to be written in here

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
    dxlSetGoalPosition(1, 512);   // Servo #1
    dxlSetGoalPosition(2, 512);
    dxlSetGoalPosition(3, 512);
    dxlSetGoalPosition(4, 512);
    dxlSetGoalPosition(5, 512);
    dxlSetGoalPosition(6, 512);
    dxlSetGoalPosition(7, 512);
    dxlSetGoalPosition(8, 512);
    dxlSetGoalPosition(9, 512);
    dxlSetGoalPosition(10, 512);
    dxlSetGoalPosition(11, 512);
    dxlSetGoalPosition(12, 512);
    dxlSetGoalPosition(13, 512);
    dxlSetGoalPosition(14, 512);
    dxlSetGoalPosition(15, 512);
    dxlSetGoalPosition(16, 512);  // Servo #16
};

//sets the speed of the two motors attached to the wheels
void Balance::SetSpeeds(){

};
