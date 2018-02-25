#include "Arduino.h"
#include "Balance.h"

/*
Describe wiring layout here
*/

Balance::Balance(float pInit, float iInit, float dInit, float desiredVal) {
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
int Balance::UpdatePID(float sensorVal) { //time is in millis, need to change so it is float/double in seconds
  //stuff that gets looped
  unsigned long previousTime = timeInstance;
  int previousError = error;
  error = setpoint - sensorVal;
  timeInstance = millis();
  double ellapsedTime = double((timeInstance - previousTime)/1000);   //(change of time)
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
  return int(outVal);
};


void Balance::SetPID(float pSet, float iSet, float dSet){
  pVal = pSet;
  iVal = iSet;
  dVal = dSet;
};

void Balance::SetDesiredVal(int desiredVal){
  setpoint = desiredVal;
};

//A group of motors
ServoGroup::ServoGroup(int initialFrame[2][NUMBER_OF_SERVOS])
{
  for(int servoNum = 0; servoNum<NUMBER_OF_ANGLE_SERVOS; servoNum++)
  {
    initialPositions[servoNum]=initialFrame[ANGLES][servoNum];
  }
  for(int idNum = 0; idNum < NUMBER_OF_SERVOS; idNum++)
  {
    idNumbers[idNum] = initialFrame[ID_NUMBERS][idNum];
  }
}

//function that is called to initialize all the dynamexl motors
void ServoGroup::ServosInitialize()
{

  //dxlSetTorqueEnable(SERVO_ID, 1); //sets torque enable
  //dxlInit(1000000); //starts dynamixel library at 1mbps
  int maxTorque = 1024;

  for(int servoIndex = 0; servoIndex < NUMBER_OF_SERVOS; servoIndex++)
  {
    int idNum = idNumbers[servoIndex];
    int torqueMode = dxlGetTorqueEnable(idNum);
    int torqueMax = dxlGetStartupMaxTorque(idNum);
    //set the first 14 servos to angle mode
    if(servoIndex < NUMBER_OF_ANGLE_SERVOS)
    {
      int dxMode = dxlGetMode(idNum);
      if(dxMode != JOINT_MODE)
      {
        axSetJointMode(idNum);
      }
    }
    //set the last two servos to wheel mode
    if(servoIndex >= NUMBER_OF_ANGLE_SERVOS)
    {
      int dxMode = dxlGetMode(idNum);
      if(dxMode != WHEEL_MODE)
      {
        axSetWheelMode(idNum);
      }
    }
    //set the Torque Enable
    if(torqueMode != 1)
    {
      dxlSetTorqueEnable(idNum, 1);
    }
    //set the max torque
    if(torqueMax != maxTorque)
    {
      dxlSetStartupMaxTorque(idNum, maxTorque);
    }
  }
};

//function that allows all motor positions (not wheel motors) to a specific orientation
void ServoGroup::SetAngles(int goalPosition[2][NUMBER_OF_SERVOS])
{
  for(int i = 0; i < NUMBER_OF_SERVOS-2; i++) {
    /***************************
    * AX Position graphic http://support.robotis.com/en/product/dynamixel/ax_series/dxl_ax_actuator.htm
    *   EXAMPLE: set servo #1 position to 512
    *     dxlSetGoalPosition(1,512);
    ****************************/
    dxlSetGoalPosition(idNumbers[i],goalPosition[0][i]);
  }
  dxlAction();
}

//sets the "speed" of the two motors attached to the wheels
//doesnt actually set speed, just the direction and proportional torque of the
//maximum output
//input must be +/-1023
void ServoGroup::SetSpeeds(int goalSpeedL, int goalSpeedR){
  /***************************
  * AX Set Goal Speed http://learn.trossenrobotics.com/projects/181-arbotix-1-6-documentation.html
  * Wheel mode; speed can be from 0 - 2047, with each increment being about .1% of total output for AX servos
  * Values from 1024-2047 rotate the servo clockwise with 1024 being stopped and 2047 being full speed
  * Essentially the 10nth bit becomes the direction control
  ****************************/
  int newSpeedL = 0;
  int newSpeedR = 0;
  if(goalSpeedL > 0)
  {
    newSpeedL = goalSpeedL;
  }
  else
  {
    newSpeedL = abs(goalSpeedL); //bit OR to scale the next 10 bits
    bitSet(newSpeedL,10); //the eleventh bit determines direction
  }
  if(goalSpeedR > 0)
  {
    newSpeedR = goalSpeedR;
  }
  else
  {
    newSpeedR = abs(goalSpeedR); //bit OR to scale the next 10 bits
    bitSet(newSpeedL,10); //the eleventh bit determines direction
  }
  dxlSetGoalSpeed(idNumbers[LEFT_MOTOR-1],newSpeedL);
  dxlSetGoalSpeed(idNumbers[RIGHT_MOTOR-1],newSpeedR);
  dxlAction();
}

/*
void ServoGroup::SetRideHeight(int height)
{
int newServoAngles[NUMBER_OF_ANGLE_SERVOS];
//copies over angles for all but legs
for()
{

}
//calculates angles for all leg joints
for()
{

}
this->SetAngles(newServoAngles);
}
*/
