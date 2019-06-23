#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include <Arduino.h>

#include "MotionSensor.h"
#include "SlaveComm.h"

// States
#define TEST_WIFI_COMMUNICATION 1
#define TEST_MOTION_SENSOR 2
#define TEST_HAPTIC_FEEDBACK 4
#define TEST_SLAVE_COMM 5

// Current State
#define STATE TEST_SLAVE_COMM

// I2C Pins for MotionSensor
#define SCL D1
#define SDA D2

// Global variables
extern MotionSensor motionSensor;
extern SlaveComm slaveComm;

class StateMachine 
{
public:
	StateMachine();
	void Current_State();
private:
	void Test_WiFi_Communication();
	void Test_Magnetometer();
	void Test_Motion_Sensor();
	void Test_Slave_Comm();
};

#endif
