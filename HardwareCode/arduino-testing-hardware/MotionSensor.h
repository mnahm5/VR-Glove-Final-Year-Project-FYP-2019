#ifndef MOTION_SENSOR_H
#define MOTION_SENSOR_H

// #include "UDPTest.h"
#include <Arduino.h>
#include <Wire.h>
#include <Ticker.h>
#include "UnityGame.h"

#define SCL D1
#define SDA D2

extern UnityGame unityGame;

class MotionSensor
{
  public:
    MotionSensor();
    void Setup();
    void Test();
  private:
  	void MPU6050_Init();
  	void Read_RawValue(uint8_t deviceAddress, uint8_t regAddress);
  	void I2C_Write(uint8_t deviceAddress, uint8_t regAddress, uint8_t data);
  	void Calibrate();
  	void ConvertRawValues();
  	void CalculateRPY();
    void PrintRPY();
    void SendRPY();
};


#endif