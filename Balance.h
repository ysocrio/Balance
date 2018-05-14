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
#define MAX_TORQUE  1023 //max value is 1023, 1/5 is recomended for smooth movement
#define STALL_TORQUE 1.5 //N*m

class Balance
{
  private:
    //tuning variables
    float kVal;
    float pVal;
    float iVal;
    float dVal;
    //desired value
    float setpoint;
    //output
    float outVal;
    //time keeping
    unsigned long timeInstance;
    unsigned long previousTime;
    bool firstTime;
    //error
    float error;
    float errorSum; //for I term
  public:
    Balance(float kInit, float pInit, float iInit, float dInit, float desiredVal);
    double UpdatePID(float sensorVal);
    void SetPID(float kSet, float pSet, float iSet, float dSet);
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
    //variable for set angles used to store value of servo that was last written to
    int lastServo;
  public:
    ServoGroup(int initialFrame[2][NUMBER_OF_SERVOS]);
    void ServosInitialize();
    void SetAnglesAll(int goalPosition[2][NUMBER_OF_SERVOS]);
    void SetAngles(int goalPosition[2][NUMBER_OF_SERVOS]);
    void SetSpeeds(int goalSpeedL, int goalSpeedR);
    //void SetRideHeight(int height);
};
#endif
