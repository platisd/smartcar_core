/*
*	Smartcar.h - A simple library for controlling the smartcar
*	by providing an interface to the Adafruit Motor library.
*	Version: 0.4
*	Author: Dimitris Platis (based on the Smartcar project by Team Pegasus)
*/
#ifndef Smartcar_h
#define Smartcar_h

#include "Arduino.h"
#include <AFMotor.h>
#include <Wire.h>
#include <HMC5883L.h>

static const short UPPER_LEFT_MOTOR_CHANNEL = 1;
static const short LOWER_LEFT_MOTOR_CHANNEL = 2;
static const short UPPER_RIGHT_MOTOR_CHANNEL = 3;
static const short LOWER_RIGHT_MOTOR_CHANNEL = 4;

static const int ROTATION_SPEED = 200; //Please do not change untill Issue#1 is resolved (see github page)
static const int MAX_SPEED = 255;
static const int MIN_SPEED = 0;

static const float PULSES_PER_CENTIMETER = 4; //determined experimentally


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
		
	private:
		void setLeftDirectionAndSpeed(int direction, int speed);
		void setRightDirectionAndSpeed(int direction, int speed);
		void setDefaultMotorSpeed(int speed);
		void travelDistance(int centimeters);
		void setInterruptPin(short pin);
		void resetCounter();
		void resetDistanceTravelled();
		AF_DCMotor motorLeft1, motorLeft2, motorRight1, motorRight2;
		unsigned short _defaultMotorSpeed, _interruptPin, _distanceTravelled;
		HMC5883L compass;
		int getMagnetometerDegrees();
		void rotateDegrees(int targetDegrees, int initialPosition, int compensation);
};

#endif
