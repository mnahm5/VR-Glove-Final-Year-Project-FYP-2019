#include "MotionSensor.h"

// MPU6050 Slave Device Address
const uint8_t MPU6050SlaveAddress = 0x68;

// sensitivity scale factor respective to full scale setting provided in datasheet 
const uint16_t AccelScaleFactor = 16384;
const uint16_t GyroScaleFactor = 131;

// MPU6050 few configuration register addresses
const uint8_t MPU6050_REGISTER_SMPLRT_DIV   =  0x19;
const uint8_t MPU6050_REGISTER_USER_CTRL    =  0x6A;
const uint8_t MPU6050_REGISTER_PWR_MGMT_1   =  0x6B;
const uint8_t MPU6050_REGISTER_PWR_MGMT_2   =  0x6C;
const uint8_t MPU6050_REGISTER_CONFIG       =  0x1A;
const uint8_t MPU6050_REGISTER_GYRO_CONFIG  =  0x1B;
const uint8_t MPU6050_REGISTER_ACCEL_CONFIG =  0x1C;
const uint8_t MPU6050_REGISTER_FIFO_EN      =  0x23;
const uint8_t MPU6050_REGISTER_INT_ENABLE   =  0x38;
const uint8_t MPU6050_REGISTER_ACCEL_XOUT_H =  0x3B;
const uint8_t MPU6050_REGISTER_SIGNAL_PATH_RESET  = 0x68;

int16_t AccelX, AccelY, AccelZ, Temperature, GyroX, GyroY, GyroZ;
float Ax, Ay, Az, T, Gx, Gy, Gz;

// Calibration
float AXoff, AYoff, AZoff;
float GXoff, GYoff, GZoff;
int numberOfTests = 100;

// PRY Calculation
float pitch = 0;
float roll = 0;
float yaw = 0;
unsigned long timer = 0;
float timeStep = 0.004;
int counter = 0;
bool flag = false;

// Yaw Filter
float yaw_prev = 0;
float yaw_drift_thresold = 0.01;

// Sending Data
String packetData;

// Interrupts
Ticker interrupt_250Hz;
bool interrupt_flag = false;
void ISR_250Hz() 
{
	interrupt_flag = true;
}

MotionSensor::MotionSensor()
{

}

void MotionSensor::Setup()
{
  MPU6050_Init();
  Calibrate();
  interrupt_250Hz.attach(timeStep, ISR_250Hz);
  Serial.println("MotionSensor Setup");
}

void MotionSensor::Test()
{
	if (interrupt_flag)
	{
		// Serial.print("ISR = ");
		// Serial.println(millis()-timer);
		// timer = millis();
		Read_RawValue(MPU6050SlaveAddress, MPU6050_REGISTER_ACCEL_XOUT_H);
		ConvertRawValues();
		CalculateRPY();

		// PrintRPY();
		SendRPY();
		interrupt_flag = false;
	}
}

void MotionSensor::PrintRPY()
{
	if (counter < 250) 
	{
		counter++;
	}
	else
	{
		counter = 0;
		// Output raw
		Serial.print("PRY: "); Serial.print(pitch); Serial.print(", "); Serial.print(roll); Serial.print(", "); Serial.println(yaw);
		Serial.println(T);
	}
}

void MotionSensor::SendRPY()
{
	packetData = "O:" + String(pitch) + ":" + String(roll) + ":" + String(yaw);
	// Serial.println(packetData);
	// UDPSend(packetData);
	if (unityGame.IsUnityGameReady())
	{
		unityGame.Send(packetData);
		// Serial.println(tokenize(flexData).c_str());
	}
}

void MotionSensor::ConvertRawValues()
{
	//divide each with their sensitivity scale factor
	Ax = (float) (AccelX-AXoff) / AccelScaleFactor;
	Ay = (float) (AccelY-AYoff) / AccelScaleFactor;
	Az = (float) (AccelZ-(AZoff-AccelScaleFactor)) / AccelScaleFactor;
	T = (float) Temperature/340+36.53; //temperature formla
	Gx = (float) (GyroX-GXoff) / GyroScaleFactor * timeStep;
	Gy = (float) (GyroY-GYoff) / GyroScaleFactor * timeStep;
	Gz = (float) (GyroZ-GZoff) / GyroScaleFactor * timeStep;
}

void MotionSensor::CalculateRPY()
{
	float pitch_a, roll_a;

	pitch_a = atan (Ax / sqrt(Ay*Ay + Az*Az)) * 180 / M_PI;
    roll_a = atan (Ay / sqrt(Ax*Ax + Az*Az)) * 180 / M_PI;
    
    pitch += Gx;
    roll += Gy;
    yaw += Gz;
    
    pitch += pitch * sin(Gz*M_PI/180);
    roll += roll * sin(Gz*M_PI/180);
    
    if (!flag)
    {
        pitch = pitch_a;
        roll = roll_a;
        flag = true;
    }
    else 
    {
        pitch = pitch * 0.98 + pitch_a * 0.02;
        roll = roll * 0.98 + roll_a * 0.02;
        yaw = yaw;
    }

    if (abs(yaw-yaw_prev) < yaw_drift_thresold) 
	{
		yaw = yaw_prev;
	}
	else
	{
		yaw_prev = yaw;
	}
}

void MotionSensor::Calibrate()
{
	Serial.println("Started MotionSensor Calibration");
	int i;
    //Count and average the first n values, defined by numberOfTests above..
    for(i=0; i<numberOfTests; i++)
    {  
    	Read_RawValue(MPU6050SlaveAddress, MPU6050_REGISTER_ACCEL_XOUT_H);
        AXoff += AccelX;
        AYoff += AccelY;
        AZoff += AccelZ;
        GXoff += GyroX;
        GYoff += GyroY;
        GZoff += GyroY;
        delay(25);
    }
    
    AXoff = AXoff/numberOfTests;
    AYoff = AYoff/numberOfTests;
    AZoff = AZoff/numberOfTests;
    GXoff = GXoff/numberOfTests;
    GYoff = GYoff/numberOfTests;
    GZoff = GZoff/numberOfTests;

    Serial.print("AXoff = ");
    Serial.print(AXoff);
    Serial.print(", AYoff = ");
    Serial.print(AYoff);
    Serial.print(", AZoff = ");
    Serial.print(AZoff);
    Serial.print(", GXoff = ");
    Serial.print(GXoff);
    Serial.print(", GYoff = ");
    Serial.print(GYoff);
    Serial.print(", GZoff = ");
    Serial.println(GZoff);
}

void MotionSensor::I2C_Write(uint8_t deviceAddress, uint8_t regAddress, uint8_t data)
{
	Wire.beginTransmission(deviceAddress);
	Wire.write(regAddress);
	Wire.write(data);
	Wire.endTransmission();
}

// read all 14 register
void MotionSensor::Read_RawValue(uint8_t deviceAddress, uint8_t regAddress)
{
	Wire.beginTransmission(deviceAddress);
	Wire.write(regAddress);
	Wire.endTransmission();
	Wire.requestFrom(deviceAddress, (uint8_t)14);
	AccelX = (((int16_t)Wire.read()<<8) | Wire.read());
	AccelY = (((int16_t)Wire.read()<<8) | Wire.read());
	AccelZ = (((int16_t)Wire.read()<<8) | Wire.read());
	Temperature = (((int16_t)Wire.read()<<8) | Wire.read());
	GyroX = (((int16_t)Wire.read()<<8) | Wire.read());
	GyroY = (((int16_t)Wire.read()<<8) | Wire.read());
	GyroZ = (((int16_t)Wire.read()<<8) | Wire.read());
}

//configure MPU6050
void MotionSensor::MPU6050_Init()
{
	delay(150);
	I2C_Write(MPU6050SlaveAddress, MPU6050_REGISTER_SMPLRT_DIV, 0x07);
	I2C_Write(MPU6050SlaveAddress, MPU6050_REGISTER_PWR_MGMT_1, 0x01);
	I2C_Write(MPU6050SlaveAddress, MPU6050_REGISTER_PWR_MGMT_2, 0x00);
	I2C_Write(MPU6050SlaveAddress, MPU6050_REGISTER_CONFIG, 0x00);
	I2C_Write(MPU6050SlaveAddress, MPU6050_REGISTER_GYRO_CONFIG, 0x00);//set +/-250 degree/second full scale
	I2C_Write(MPU6050SlaveAddress, MPU6050_REGISTER_ACCEL_CONFIG, 0x00);// set +/- 2g full scale
	I2C_Write(MPU6050SlaveAddress, MPU6050_REGISTER_FIFO_EN, 0x00);
	I2C_Write(MPU6050SlaveAddress, MPU6050_REGISTER_INT_ENABLE, 0x01);
	I2C_Write(MPU6050SlaveAddress, MPU6050_REGISTER_SIGNAL_PATH_RESET, 0x00);
	I2C_Write(MPU6050SlaveAddress, MPU6050_REGISTER_USER_CTRL, 0x00);
}
