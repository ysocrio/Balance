/*
  Balance.h library
  Using this to organize our classes
*/

#ifndef Balance_h
#define Balance_h
//these two lines check if balance has already been instantiated
#include "Arduino.h"
//standard arduino data types
#include <Wire.h>             //i2c library

//definitions for all the MPU6050 used by class Sensor
#define MPU_addr 0x68 //address of MPU6050
#define MPU_PWR_MGMT_1 0x6B
#define MPU_ACCEL_XOUT_H 0x3B
#define MPU_ACCEL_XOUT_L 0x3C
#define MPU_ACCEL_YOUT_H 0x3D
#define MPU_ACCEL_YOUT_L 0x3E
#define MPU_ACCEL_ZOUT_H 0x3F
#define MPU_ACCEL_ZOUT_L 0x40
#define AX12_CWLO 0X06
#define AX12_CWHI 0X07
#define AX12_CCWLO 0X08
#define AX12_CCWJI 0x09
#define SETLOW 0x00
#define SETCCWLO 0XFF
#define SETCCWHI 0X03
#define CLEAR 0

struct orientationVals {
  int accelX;
  int accelY;
  int accelZ;
  int temp;
  int gyroX;
  int gyroY;
  int gyroZ;
};

class Balance
{
  private:
    //tuning variables
    double pVal;
    double iVal;
    double dVal;
    //desired value
    int setpoint;
    //output
    int outVal;
    //time keeping
    unsigned long timeInstance;
    //error
    int error;
    double errorSum; //for I term
  public:
    Balance(double pInit, double iInit, double dInit, int desiredVal);
    int UpdatePID(int sensorVal);
    void SetPID(int pSet, int iSet, int dSet);
    void SetDesiredVal(int desiredVal);
    void ServosInitialize();
    void SetFrame();
    void SetSpeeds(int goalSpeed1, int goalSpeed2);
};
class Sensor
{
  private:
      int updatePeriod;
      unsigned long lastTimeInstance;
      orientationVals sensorVals;
  public:
    Sensor();
    void Connect();
    void Update();
    double GetPitchAngle();
};
#endif
