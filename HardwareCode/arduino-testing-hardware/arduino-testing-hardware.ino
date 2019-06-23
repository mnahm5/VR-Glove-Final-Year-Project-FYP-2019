#include "StateMachine.h"
#include "UnityGame.h"

StateMachine stateMachine;
MotionSensor motionSensor;
//HapticFeedback hapticFeedback;
SlaveComm slaveComm;
UnityGame unityGame;

void setup()
{
	Serial.begin(115200);
	Wire.begin(SDA, SCL);
	slaveComm.Setup();
	unityGame.Setup();
	motionSensor.Setup();
	//hapticFeedback.Setup();
	Serial.println("Setup Complete");
}

void loop()
{
	//stateMachine.Current_State();
	motionSensor.Test();
	slaveComm.Loop();
	unityGame.Loop();
}
