#include "Arduino.h"
#include "Balance.h"

/*
Describe wiring layout here
*/

Balance::Balance(float kInit, float pInit, float iInit, float dInit, float desiredVal) {
  //initialize the object
  //tuningValues
  kVal = kInit;
  pVal = pInit;
  iVal = iInit;
  dVal = dInit;
  //time
  timeInstance = 0;
  previousTime = 0;
  firstTime = true;
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
double Balance::UpdatePID(float sensorVal) { //time is in millis, need to change so it is float/double in seconds
  //stuff that gets looped
//FIX I KICK (due to )

  timeInstance = micros();
  float elapsedTime = float(timeInstance - previousTime)/1000000;   //(change of time)
  if (elapsedTime != 0)
  {
    float previousError = error;
    error = setpoint - sensorVal;
    float errorChange = error - previousError;          //(change in error)
    //proportional term
    outVal = pVal * error;
    //integral term
    if(firstTime){
      //gets rid of first time kick due to I value
      elapsedTime = 0;
      firstTime=false;
    }
    errorSum += elapsedTime * error;
    outVal += errorSum * iVal;
    //derivative term
    float derivE = errorChange / elapsedTime;
    outVal += derivE * dVal;
  }
  previousTime = timeInstance;
  return float(outVal*kVal);
};


void Balance::SetPID(float kSet, float pSet, float iSet, float dSet){
  kVal = kSet;
  pVal = pSet;
  iVal = iSet;
  dVal = dSet;
};
void Balance::SetPIDLive(float kSet, float pSet, float iSet, float dSet){
  kVal = kSet;
  pVal = pSet;
  iVal = iSet;
  dVal = dSet;
  //time
  timeInstance = 0;
  previousTime = 0;
  firstTime = true;
  //error
  error = 0;
  errorSum = 0;
};

void Balance::SetDesiredVal(int desiredVal){
  setpoint = desiredVal;
};

//A group of motors
ServoGroup::ServoGroup(int initialFrame[2][NUMBER_OF_SERVOS])
{
  //initialize lastServo
  lastServo = 0;
  //format initialPositions and idNumbers
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
  int maxTorque = 1023;

  for(int servoIndex = 0; servoIndex < NUMBER_OF_SERVOS; servoIndex++)
  {
    int idNum = idNumbers[servoIndex];
    int torqueMode = dxlGetTorqueEnable(idNum);
    int torqueMax = dxlGetStartupMaxTorque(idNum);
    int torqueLimit = dxlGetTorqueLimit(idNum);
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

  /***************************
  * AX Position graphic http://support.robotis.com/en/product/dynamixel/ax_series/dxl_ax_actuator.htm
  *   EXAMPLE: set servo #1 position to 512
  *     dxlSetGoalPosition(1,512);
  ****************************/

  //function that allows all motor positions (not wheel motors) to a specific orientation
  void ServoGroup::SetAnglesAll(int goalPosition[2][NUMBER_OF_SERVOS])
  {
    for(int i = 0; i < NUMBER_OF_SERVOS-2; i++) {
      dxlSetGoalPosition(idNumbers[i],goalPosition[0][i]);
    }
    dxlAction();
  }

  //function that allows all motor positions (not wheel motors) to a specific orientation
  void ServoGroup::SetAngles(int goalPosition[2][NUMBER_OF_SERVOS])
  {
    if(lastServo >= NUMBER_OF_SERVOS-2)
    {
      lastServo = 0;
    }
    //sets servo number "lastServo" to its given goal position
    dxlSetGoalPosition(idNumbers[lastServo],goalPosition[0][lastServo]);
    //move to next servo number
    if(lastServo < NUMBER_OF_SERVOS-2)
    {
      lastServo++;
    }
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
    bitClear(newSpeedL,10);
  }
  else if(goalSpeedL != 0)
  {
    newSpeedL = abs(goalSpeedL); //bit OR to scale the next 10 bits
    bitSet(newSpeedL,10); //the eleventh bit determines direction
  }
  else
  {
    newSpeedL = 0;
  }

  if(goalSpeedR > 0)
  {
    newSpeedR = goalSpeedR;
    bitClear(newSpeedR,10);
  }
  else if(goalSpeedR != 0)
  {
    newSpeedR = abs(goalSpeedR); //bit OR to scale the next 10 bits
    bitSet(newSpeedR,10); //the eleventh bit determines direction
  }
  else
  {
    newSpeedR = 0;
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
