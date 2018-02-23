/*
  Movement.h library
  New library for movements
  For organizing classes
*/

#ifndef Movement_h
#define Movement_h
//these check if the movement has already been started

#include "Arduino.h"
#include "ax12.h" //dynamex1 servos

//standard arduino data types

#define CLEAR 0
#define NUMBER_OF_SERVOS 16
#define NUMBER_OF_ANGLE_SERVOS 14
#define ANGLES 0
#define ID_NUMBERS 1
#define LEFT_MOTOR 15
#define RIGHT_MOTOR 16
#define MAX_SPEED_CW 2047 //RANGE IS 1024-2047
#define MAX_SPEED_CCW 1023 //RANGE IS 0-1024
#define MAX_TORQUE  205 //max value is 1023, 1/5 is recomended for smooth movement
#define STALL_TORQUE 1.5 //N*m 

class Balance
{
  private:
    //tuning variables
    double pVal;
    double iVal;
    double dVal;
    //desired value
    float setpoint;
    //output
    double outVal;
    //time keeping
    unsigned long timeInstance;
    //error
    int error;
    double errorSum; //for I term
  public:
    Balance(double pInit, double iInit, double dInit, float desiredVal);
    int UpdatePID(float sensorVal);
    void SetPID(int pSet, int iSet, int dSet);
    void SetDesiredVal(int desiredVal);
/*    void ServosInitialize();
    void SetFrame(int goalPosition[16]);
    void SetSpeeds(int goalSpeedL, int goalSpeedR);
*/
};
class ServoGroup
{
  private:
    int initialPositions[NUMBER_OF_ANGLE_SERVOS];
    int idNumbers[NUMBER_OF_SERVOS];
  public:
    void SetSpeeds(int goalSpeedL, int goalSpeedR);
};
#endif
