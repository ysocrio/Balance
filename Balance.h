/*
  Balance.h library
  Using this to organize our classes
*/

#ifndef Balance_h
#define Balance_h
//these two lines check if balance has already been instantiated

#include "Arduino.h"
#include "ax12.h"     //for dynamexl servos

//standard arduino data types


//definitions for AX12+
#define AX12_CWLO 0X06
#define AX12_CWHI 0X07
#define AX12_CCWLO 0X08
#define AX12_CCWHI 0x09
#define SETLOW 0x00
#define SETCCWLO 0XFF
#define SETCCWHI 0X03
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
    double NVal;
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
    Balance(double pInit, double iInit, double dInit, double NInit, float desiredVal);
    int UpdatePID(float sensorVal);
    int UpdatePIDN(float sensorVal);
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
    ServoGroup(int initialFrame[2][NUMBER_OF_SERVOS]);
    void ServosInitialize();
    void SetAngles(int goalPosition[2][NUMBER_OF_SERVOS]);
    void SetSpeeds(int goalSpeedL, int goalSpeedR);
    //void SetRideHeight(int height);
};
#endif
