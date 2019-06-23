#ifndef UNITY_GAME_H
#define UNITY_GAME_H

#include <Arduino.h>
#include <Wire.h>
#include <Ticker.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <cstring>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

class UnityGame
{
  public:
    UnityGame();
    void Setup();
    void Loop();
    void Send(String packet);
    bool IsUnityGameReady();
    string GetLatestHapticCmd();
    string GetLatestGripCmd();
    void ResetLatestHapticCmd();
    void ResetLatestGripCmd();
  private:
	void Receive();
	void ParseReceviedData();
	IPAddress GetBroadcastAddress(IPAddress ip);
};

#endif