/*
*	Smartcar.h - A simple library for controlling the smartcar
*	by providing an interface to the Adafruit Motor library.
*	Version: 0.1
*/

#include "Arduino.h"
#include "Smartcar.h"
#include <AFMotor.h>

Smartcar::Smartcar() : motorLeft1(1), motorLeft2(2), motorRight1(3), motorRight2(4)
{
	setDefaultMotorSpeed(200);
	setLeftDirectionAndSpeed(RELEASE, 0);
	setRightDirectionAndSpeed(RELEASE,0);
}

void Smartcar::goForward(){
	setLeftDirectionAndSpeed(FORWARD, _defaultMotorSpeed);
	setRightDirectionAndSpeed(FORWARD, _defaultMotorSpeed);
}
void Smartcar::goForward(int centimeters){} //TO-DO

void Smartcar::goBackward(){
	setLeftDirectionAndSpeed(BACKWARD, _defaultMotorSpeed);
	setRightDirectionAndSpeed(BACKWARD, _defaultMotorSpeed);
}
void Smartcar::goBackward(int centimeters){} //TO-DO

void Smartcar::steerFrontRight(){
	setLeftDirectionAndSpeed(FORWARD, MAX_SPEED);
	setRightDirectionAndSpeed(FORWARD, _defaultMotorSpeed);
}
void Smartcar::steerFrontLeft(){
	setLeftDirectionAndSpeed(FORWARD, _defaultMotorSpeed);
	setRightDirectionAndSpeed(FORWARD, MAX_SPEED);
}
void Smartcar::steerBackRight(){
	setLeftDirectionAndSpeed(BACKWARD, MAX_SPEED);
	setRightDirectionAndSpeed(BACKWARD, _defaultMotorSpeed);
}
void Smartcar::steerBackLeft(){
	setLeftDirectionAndSpeed(BACKWARD, _defaultMotorSpeed);
	setRightDirectionAndSpeed(BACKWARD, MAX_SPEED);
}
void Smartcar::rotateClockwise(){
	setLeftDirectionAndSpeed(FORWARD, MAX_SPEED);
	setRightDirectionAndSpeed(BACKWARD, MAX_SPEED);
}
void Smartcar::rotateClockwise(int degrees){} //TO-DO

void Smartcar::rotateCounterClockwise(){
	setLeftDirectionAndSpeed(BACKWARD, MAX_SPEED);
	setRightDirectionAndSpeed(FORWARD, MAX_SPEED);
}
void Smartcar::rotateCounterClockwise(int degrees){} //TO-DO

void Smartcar::stop(){
	setLeftDirectionAndSpeed(RELEASE, 0);
	setRightDirectionAndSpeed(RELEASE,0);
}
void Smartcar::setLeftMotorsDirection(int direction){
	motorLeft1.run(direction);
	motorLeft2.run(direction);
}
void Smartcar::setRightMotorsDirection(int direction){
	motorRight1.run(direction);
	motorRight2.run(direction);
}
void Smartcar::setLeftMotorsSpeed(int speed){
	motorLeft1.setSpeed(speed);
	motorLeft2.setSpeed(speed);
}
void Smartcar::setRightMotorsSpeed (int speed){
	motorRight1.setSpeed(speed);
	motorRight2.setSpeed(speed);
}

void Smartcar::setLeftDirectionAndSpeed(int direction, int speed){
	setLeftMotorsDirection(direction);
	setLeftMotorsSpeed(speed);
}

void Smartcar::setRightDirectionAndSpeed(int direction, int speed){
	setRightMotorsDirection(direction);
	setRightMotorsSpeed(speed);
}

void Smartcar::setDefaultMotorSpeed(int speed){
	_defaultMotorSpeed = constrain(speed, MIN_SPEED, MAX_SPEED);
}
