#include "StateMachine.h"

StateMachine::StateMachine()
{

}

void StateMachine::Current_State()
{
	#if STATE==TEST_WIFI_COMMUNICATION
		Test_WiFi_Communication();
	#endif
	#if STATE==TEST_MOTION_SENSOR
		Test_Motion_Sensor();
	#endif
	#if STATE==TEST_SLAVE_COMM
		Test_Slave_Comm();
	#endif
}

void StateMachine::Test_WiFi_Communication()
{
	//UDPLoop();
	//HandleClient();
}

void StateMachine::Test_Motion_Sensor()
{
	motionSensor.Test();
}

void StateMachine::Test_Slave_Comm()
{
	slaveComm.Loop();
}
