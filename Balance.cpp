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

void Balance::SetPID(int pSet, int iSet, int dSet){
  pVal = pSet;
  iVal = iSet;
  dVal = dSet;
};

void Balance::SetDesiredVal(int desiredVal){
  setpoint = desiredVal;
};

//function that is called to initialize all the dynamexl motors
void Balance::ServosInitialize()
{
    for(int servoID=1; servoID<= 16; servoID++)
    {
       if(servoID<=14)
       {
         dxlSetRegister(servoID,AX12_CWLO,SETLOW);//Lowest byte of clockwise angle limit,@ initial value to make joint mode
         dxlSetRegister(servoID,AX12_CWHI,SETLOW);//Highest byte of clockwise angle limit,@ initial value
         dxlSetRegister(servoID,AX12_CCWLO,SETCCWLO);//Lowest byte of counterclockwise angle limit,@ initial value
         dxlSetRegister(servoID,AX12_CCWHI,SETCCWHI);//Highest byte of counterclockwise angle limit,@ initial value
       }
       if(servoID== 15 || servoID==16)
       {
         dxlSetRegister(servoID,AX12_CWLO,SETLOW);//Lowest byte of clockwise angle limit,@ initial value to make wheel mode
         dxlSetRegister(servoID,AX12_CWHI,SETLOW);//Highest byte of clockwise angle limit,@ initial value
         dxlSetRegister(servoID,AX12_CCWLO,SETLOW);//Lowest byte of counterclockwise angle limit,@ initial value
         dxlSetRegister(servoID,AX12_CCWHI,SETLOW);//Highest byte of counterclockwise angle limit,@ initial value
       }
    }
};

//function that allows all motor positions (not wheel motors) to a specific orientation
void Balance::SetFrame(int goalPosition[16])
{
  for(int i = 1; i <= 16; i++) {
    /***************************
    * AX Position graphic http://support.robotis.com/en/product/dynamixel/ax_series/dxl_ax_actuator.htm
    *   EXAMPLE: set servo #1 position to 512
    *     dxlSetGoalPosition(1,512);
    ****************************/
    dxlSetGoalPosition(i, goalPosition[i-1]);
  }
}

//sets the speed of the two motors attached to the wheels
void Balance::SetSpeeds(int goalSpeedL, int goalSpeedR){
    /***************************
    * AX Set Goal Speed http://learn.trossenrobotics.com/projects/181-arbotix-1-6-documentation.html
    * Wheel mode; speed can be from 0 - 2047, with each increment being about .1% of total output for AX servos
    * Values from 1024-2047 rotate the servo clockwise with 1024 being stopped and 2047 being full speed
    * Essentially the 10nth bit becomes the direction control
    ****************************/
        dxlSetGoalSpeed(15,goalSpeedL);
        dxlSetGoalSpeed(16,goalSpeedR);
}

Sensor::Sensor(int updatePeriodSet){
  updatePeriod = updatePeriodSet; //in ms, checks sensor board twice every second
  lastTimeInstance = millis();
};

void Sensor::Connect()    //called in setup to connect to IMU6050
{
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(MPU_PWR_MGMT_1);
  Wire.write(CLEAR);
  //sets MPU_PWR_MGMT_1 to zero, brings the sensor out of sleep mode
  Wire.endTransmission(true);
  //Wire.write moves data into a buffer, endtransmission sends data
  //if argument is parameter is true, connection is ended afterwards, if false
  //then connection will keep connection active
};

//method to return last sensor reading
//when time from last sensor reading is greater than updatePeriod,
//sensor values are updated
void Sensor::Update()
{
  signed long currentTime = millis();
  int timeDifference = int(currentTime - lastTimeInstance);
  if(timeDifference >= updatePeriod)
  {
    Wire.beginTransmission(MPU_addr);
    Wire.write(MPU_ACCEL_XOUT_H); //starting register to already
    Wire.endTransmission(false);
    Wire.requestFrom(MPU_addr, 14, true);//requests 14 registers

    sensorVals.accelX = (Wire.read()<<8)|(Wire.read());
    //first read is highest 8 bits, so we shift that, then OR with lowest 8 bits
    sensorVals.accelY = (Wire.read()<<8)|(Wire.read());
    sensorVals.accelX = (Wire.read()<<8)|(Wire.read());
    sensorVals.temp = (Wire.read()<<8)|(Wire.read());
    sensorVals.gyroX = (Wire.read()<<8)|(Wire.read());
    sensorVals.gyroY = (Wire.read()<<8)|(Wire.read());
    sensorVals.gyroZ = (Wire.read()<<8)|(Wire.read());

    lastTimeInstance = millis();
  }
};

double Sensor::GetPitchAngle(){
  return sensorVals.gyroX;
}
