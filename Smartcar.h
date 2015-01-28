/*
*	Smartcar.h - A simple library for controlling the smartcar
*	by providing an interface to the Adafruit Motor library.
*	Version: 0.3
*	Author: Dimitris Platis (based on the Smartcar project by Team Pegasus)
*/
#ifndef Smartcar_h
#define Smartcar_h

#include "Arduino.h"
#include <AFMotor.h>


static const short UPPER_LEFT_MOTOR_PIN = 1;
static const short LOWER_LEFT_MOTOR_PIN = 2;
static const short UPPER_RIGHT_MOTOR_PIN = 3;
static const short LOWER_RIGHT_MOTOR_PIN = 4;

static const int ROTATION_SPEED = 200; //Please do not change untill Issue#1 is resolved (see github page)
static const int MAX_SPEED = 255;
static const int MIN_SPEED = 0;

static const float PULSES_PER_CENTIMETER = 4.9; //determined empirically


void updateCounter();

class Smartcar
{
	public:
		Smartcar();
		void goForward();
		void goForward(int centimeters);
		void goBackward();
		void goBackward(int centimeters);
		void turnFrontRight();
		void turnFrontLeft();
		void turnBackRight();
		void turnBackLeft();
		void rotateClockwise();
		void rotateClockwise(int degrees);
		void rotateCounterClockwise();
		void rotateCounterClockwise(int degrees);
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
		void initializeMagnetometer();
		int getMagnetometerData();
		AF_DCMotor motorLeft1, motorLeft2, motorRight1, motorRight2;
		unsigned short _defaultMotorSpeed, _interruptPin, _distanceTravelled;

};

#endif
