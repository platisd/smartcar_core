/*
  Smartcar.h - A simple library for controlling the smartcar
*/
#ifndef Smartcar_h
#define Smartcar_h

#include "Arduino.h"
#include <AFMotor.h>

static const int MAX_SPEED = 255;
static const int MIN_SPEED = 0;

class Smartcar
{
	public:
		Smartcar();
		void goForward();
		void goForward(int centimeters);
		void goBackward();
		void goBackward(int centimeters);
		void steerFrontRight();
		void steerFrontLeft();
		void steerBackRight();
		void steerBackLeft();
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
		AF_DCMotor motorLeft1, motorLeft2, motorRight1, motorRight2;
		short _defaultMotorSpeed;
};

#endif
