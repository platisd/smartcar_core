/*
*	Smartcar.h - A simple library for controlling the smartcar
*	by providing an interface to the Adafruit Motor library.
*	Version: 0.5
*	Author: Dimitris Platis (based on the Smartcar project by Team Pegasus)
*/
#ifndef Smartcar_h
#define Smartcar_h

#include "Arduino.h"
#include <AFMotor.h>
#include <Wire.h>

/* ====== Motor shield constants ====== */
static const short UPPER_LEFT_MOTOR_CHANNEL = 1;
static const short LOWER_LEFT_MOTOR_CHANNEL = 2;
static const short UPPER_RIGHT_MOTOR_CHANNEL = 3;
static const short LOWER_RIGHT_MOTOR_CHANNEL = 4;

static const int DEFAULT_MOTOR_SPEED = 200;
static const int DEFAULT_ROTATION_SPEED = 200; //Please do not increase more than 200 untill Issue#1 is resolved (see github page)
static const int MAX_SPEED = 255;
static const int MIN_SPEED = 0;

static const int AUTOMATION_MOTOR_SPEED = 85;
static const int AUTOMATION_ROTATION_SPEED = 85;

/* ====== Odometer (speed encoder) constants ====== */
static const float PULSES_PER_CENTIMETER = 4; //determined experimentally
static const int ODOMETER_PIN = 4;

/* ====== Gyroscope (L3G4200D) constants ====== */
static const int GYRO_OFFSET = 20;
static const int GYRO_SAMPLING_RATE = 20;
static const float GYRO_SENSITIVITY = 0.07;

static const int CTRL_REG1 = 0x20;
static const int CTRL_REG2 =  0x21;
static const int CTRL_REG3 = 0x22;
static const int CTRL_REG4 = 0x23;
static const int CTRL_REG5 = 0x24;

static const int L3G4200D_Address = 105; //gyroscope I2C address


void updateCounter();

class Smartcar
{
	public:
		Smartcar();
		void begin();
		void goForward();
		void goForward(int centimeters);
		void goBackward();
		void goBackward(int centimeters);
		void turnFrontRight();
		void turnFrontLeft();
		void turnBackRight();
		void turnBackLeft();
		void rotateClockwise();
		void rotateClockwise(int targetDegrees);
		void rotateCounterClockwise();
		void rotateCounterClockwise(int targetDegrees);
		void stop();
		void setLeftMotorsDirection(int direction);
		void setRightMotorsDirection(int direction);
		void setLeftMotorsSpeed(int speed);
		void setRightMotorsSpeed (int speed);
		void setAutomationMotorSpeed(int automationSpeed)
		void setAutomationRotationSpeed(int rotationSpeed);
		
	private:
		void setLeftDirectionAndSpeed(int direction, int speed);
		void setRightDirectionAndSpeed(int direction, int speed);
		void setDefaultMotorSpeed(int speed);
		void setDefaultRotationSpeed(int speed);
		void restoreDefaultMotorSpeed();
		void restoreDefaultRotationSpeed();
		void travelDistance(int centimeters);
		void setOdometerInterruptPin(short pin);
		void resetCounter();
		void resetDistanceTravelled();
		AF_DCMotor motorLeft1, motorLeft2, motorRight1, motorRight2;
		unsigned short _defaultMotorSpeed, _odometerInterruptPin, _distanceTravelled, _defaultRotationSpeed;
		void angularDisplacement(int targetDegrees);
		void initializeGyro(int gyroscopeOffset, int gyroscopeSamplingRate,float gyroscopeSensitivity);
		int getGyroValues(), setupL3G4200D(int scale), readRegister(int deviceAddress, byte address);
		void writeRegister(int deviceAddress, byte address, byte val);
		int _gyroscopeSamplingRate, _gyroscopeOffset;
		float  _gyroscopeSensitivity;
		int _automationMotorSpeed, _automationRotationSpeed;

};

#endif
