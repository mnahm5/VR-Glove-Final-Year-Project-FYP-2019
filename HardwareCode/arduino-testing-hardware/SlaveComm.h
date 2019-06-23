#ifndef SLAVE_COMM_H
#define SLAVE_COMM_H

#include <Arduino.h>
#include <Wire.h>
#include <cstring>
#include <vector>
#include <string>
#include <sstream>
#include <Ticker.h>
#include "UnityGame.h"

using namespace std;

#define PSOC_SLAVE_ADDRESS 0x07
#define NO_OF_FLEX_SENSORS 10

extern UnityGame unityGame;

class SlaveComm
{
  public:
    SlaveComm();
    void Setup();
    void Loop();

    void SendString(string data);

    string GetData(int noOfBytes);
    
    void GetUpdatedFlexSensorData(int noOfSensors);
    void PrintFlexData(string collectedData, int noOfSensors);
  private:
  	void SendReset();
    string tokenize(string& s);
};

#endif