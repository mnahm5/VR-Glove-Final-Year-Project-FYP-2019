#include "UnityGame.h"
//
//const char* ssid = "LAPTOP-5D1SHSVD 7717";
//const char* password = "2122R|s1";
const char* ssid = "DESKTOP-BCQ1O67 3578";
const char* password = "97kG7-16";

WiFiUDP Udp;
String NodeIP = "";                 // for storing IP to send to PC/Phone
char incomingPacket[255];           // buffer for incoming packets

char charBuf[50] = "";

// Recevied Data
char latestPacket[255];
vector <string> separatedData;

// IPs and Ports
bool unityReady = false;
unsigned int localUdpPort = 4210;   // local port to listen for packets
unsigned int unityUdpPort = 51220;
IPAddress unityIp;
IPAddress localBroadcastIp;

string hapticCmd;
string gripCmd;

UnityGame::UnityGame()
{

}

void UnityGame::Setup()
{
  ResetLatestHapticCmd();
  ResetLatestGripCmd();

  Serial.printf("Connecting to %s ", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" connected");

  Udp.begin(localUdpPort);
  NodeIP = WiFi.localIP().toString();
  Serial.printf("Now listening at IP %s, UDP port %d\n", NodeIP.c_str(), localUdpPort);
  localBroadcastIp = GetBroadcastAddress(WiFi.localIP());
  Serial.println("UnityGame Setup");
}

void UnityGame::Loop()
{
  if (!unityReady)
  {
    Serial.println("Setting up with Unity Game");
    Send("Ready");
    delay(1000);
  }
  else
  {
    // Start doing stuff
  }
  Receive();
}

void UnityGame::Send(String packet)
{
  // Send data
  char charBuf[255];
  if (unityReady)
    Udp.beginPacket(unityIp, unityUdpPort);
  else
    Udp.beginPacket(localBroadcastIp, unityUdpPort);
  packet.toCharArray(charBuf, 255);
  Udp.write(charBuf);
  Udp.endPacket();
}

void UnityGame::Receive()
{
  // Check for received data
  int packetSize = Udp.parsePacket();
  if (packetSize)
  {
    // Serial.printf("Received %d bytes from %s, port %d\n", packetSize, Udp.remoteIP().toString().c_str(), Udp.remotePort());
    int len = Udp.read(incomingPacket, 255);
    if (len > 0)
    {
      incomingPacket[len] = 0;
    }
    strcpy(latestPacket, incomingPacket);

    // Serial.println(latestPacket);

    if (unityReady)
      ParseReceviedData();
    else
    {
      if (strcmp(latestPacket, "Ready") == 0)
      {
        unityUdpPort = Udp.remotePort();
        unityIp = Udp.remoteIP();
        unityReady = true;
        Serial.printf("Connected to IP=%s Port=%d\n", unityIp.toString().c_str(), unityUdpPort);
      }
    }
  }
}

void UnityGame::ParseReceviedData()
{
  // Send Haptic Data to PSoC Slave
  if (strlen(latestPacket) > 2 && latestPacket[0] == 'H' && latestPacket[1] == ':')
  {
    hapticCmd = latestPacket;
  }
  else if (strlen(latestPacket) > 2 && latestPacket[0] == 'G' && latestPacket[1] == ':')
  {
    gripCmd = latestPacket;
  }
  else
  {
    Serial.printf("Don't recognise cmd = '%s'\n", latestPacket);
  }
}

IPAddress UnityGame::GetBroadcastAddress(IPAddress ip)
{
  IPAddress broadcastIp;
  for (int i = 0; i < 3; i++)
  {
    broadcastIp[i] = ip[i];
  }
  broadcastIp[3] = 255;
  return broadcastIp;
}

bool UnityGame::IsUnityGameReady()
{
  return unityReady;
}

string UnityGame::GetLatestHapticCmd()
{
  return hapticCmd;
}

string UnityGame::GetLatestGripCmd()
{
  return gripCmd;
}

void UnityGame::ResetLatestHapticCmd()
{
  hapticCmd = "";
}

void UnityGame::ResetLatestGripCmd()
{
  gripCmd = "";
}
