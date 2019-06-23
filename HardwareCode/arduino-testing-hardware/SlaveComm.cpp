#include "SlaveComm.h"

// Interrupts
float timeStepFlexDataPolling = 0.008; // in seconds
Ticker interruptFlexDataPolling;
bool interruptFlexDataPollingFlag = false;
void IsrFlexDataPolling() 
{
	interruptFlexDataPollingFlag = true;
}

// FlexData to be sent
string flexData;

SlaveComm::SlaveComm()
{

}

void SlaveComm::Setup()
{
	SendReset();
	interruptFlexDataPolling.attach(timeStepFlexDataPolling, IsrFlexDataPolling);
	Serial.println("SlaveComm Reset");
}

void SlaveComm::Loop()
{
	if (interruptFlexDataPollingFlag)
	{
		GetUpdatedFlexSensorData(NO_OF_FLEX_SENSORS);
		interruptFlexDataPollingFlag = false;

		if (unityGame.IsUnityGameReady())
		{
			unityGame.Send(tokenize(flexData).c_str());
			 Serial.println(tokenize(flexData).c_str());
		}
	}
	if (unityGame.GetLatestHapticCmd() != "")
	{
		SendString(unityGame.GetLatestHapticCmd());
		Serial.printf("Sent out %s\n", unityGame.GetLatestHapticCmd().c_str());
		unityGame.ResetLatestHapticCmd();
	}
	if (unityGame.GetLatestGripCmd() != "")
	{
		SendString(unityGame.GetLatestGripCmd());
		Serial.printf("Sent out %s\n", unityGame.GetLatestGripCmd().c_str());
		unityGame.ResetLatestGripCmd();
	}
}

void SlaveComm::SendString(string data)
{
	Wire.beginTransmission(PSOC_SLAVE_ADDRESS);
	Wire.write(data.c_str());
	Wire.endTransmission();
}

string SlaveComm::GetData(int noOfBytes)
{
	string receivedData;
	Wire.requestFrom(PSOC_SLAVE_ADDRESS, noOfBytes);
	while(Wire.available())
	{
		char c = Wire.read();
		receivedData.push_back(c);
	}
	return receivedData;
}

void SlaveComm::GetUpdatedFlexSensorData(int noOfSensors)
{
	SendString("flexData");
	flexData = GetData(30);
	SendString("Done");
//	PrintFlexData(flexData, 10);
}

void SlaveComm::PrintFlexData(string collectedData, int noOfSensors)
{
	for (int i = 0; i < noOfSensors; i++)
	{
		string data = "";
		for (int j = i*3; j < (i+1)*3; j++)
		{
			data += collectedData[j];
		}
		unsigned int x;   
		std::stringstream ss;
		ss << std::hex << data;
		ss >> x;
		Serial.println(x);
	}
}

void SlaveComm::SendReset()
{
	SendString("Reset");
}

string SlaveComm::tokenize(string& s) 
{
	string output = "F";
	for (int i = 0; i < s.size(); i++)
	{
		if (i % 3 == 0)
		{
			output.push_back(':');
		}
		output.push_back(s[i]);
	}
	return output;
}
