/*
  Balance.h library
  Using this to organize our classes
*/

#ifndef Balance_h
#define Balance_h
//these two lines check if balance has already been instantiated
#include "Arduino.h"
//standard arduino data types

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
    void SetSpeeds();
};
class Sensor
{
  private:
  public:
    Sensor();
    void Connect();
    double GetPitchAngle();
};
#endif
