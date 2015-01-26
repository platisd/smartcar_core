/*
*	Smartcar.h - A simple library for controlling the smartcar
*	by providing an interface to the Adafruit Motor library.
*	Version: 0.2
*	Author: Dimitris Platis (based on the Smartcar project by Team Pegasus)
*/
#include "Smartcar.h"

volatile unsigned short _pulseCounter = 0;

Smartcar::Smartcar() : motorLeft1(UPPER_LEFT_MOTOR_PIN), motorLeft2(LOWER_LEFT_MOTOR_PIN), motorRight1(UPPER_RIGHT_MOTOR_PIN), motorRight2(LOWER_RIGHT_MOTOR_PIN)
{
	setDefaultMotorSpeed(200);
	setLeftDirectionAndSpeed(RELEASE, 0);
	setRightDirectionAndSpeed(RELEASE,0);
	setInterruptPin(4);
}

void Smartcar::goForward(){
	setLeftDirectionAndSpeed(FORWARD, _defaultMotorSpeed);
	setRightDirectionAndSpeed(FORWARD, _defaultMotorSpeed);
}
void Smartcar::goForward(int centimeters){
	goForward();
	travelDistance(centimeters);
	stop();
}

void Smartcar::goBackward(){
	setLeftDirectionAndSpeed(BACKWARD, _defaultMotorSpeed);
	setRightDirectionAndSpeed(BACKWARD, _defaultMotorSpeed);
}
void Smartcar::goBackward(int centimeters){
	goBackward();
	travelDistance(centimeters);
	stop();
}

void Smartcar::turnFrontRight(){
	setLeftDirectionAndSpeed(FORWARD, MAX_SPEED);
	setRightDirectionAndSpeed(FORWARD, _defaultMotorSpeed/3);
}
void Smartcar::turnFrontLeft(){
	setLeftDirectionAndSpeed(FORWARD, _defaultMotorSpeed/3);
	setRightDirectionAndSpeed(FORWARD, MAX_SPEED);
}
void Smartcar::turnBackRight(){
	setLeftDirectionAndSpeed(BACKWARD, MAX_SPEED);
	setRightDirectionAndSpeed(BACKWARD, _defaultMotorSpeed/3);
}
void Smartcar::turnBackLeft(){
	setLeftDirectionAndSpeed(BACKWARD, _defaultMotorSpeed/3);
	setRightDirectionAndSpeed(BACKWARD, MAX_SPEED);
}
void Smartcar::rotateClockwise(){
	setLeftDirectionAndSpeed(FORWARD, MAX_SPEED);
	setRightDirectionAndSpeed(BACKWARD, MAX_SPEED);
}
void Smartcar::rotateClockwise(int degrees){ //TO-DO
	initializeMagnetometer();
	while ((degrees - getMagnetometerData()) < 2){
		rotateClockwise();
	}
	stop();
}


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

void Smartcar::setInterruptPin(short pin){
	_interruptPin = pin;
}

void Smartcar::travelDistance(int centimeters){
	attachInterrupt(_interruptPin, updateCounter, RISING);
	resetCounter();
	resetDistanceTravelled();
	while (centimeters > _distanceTravelled){
		_distanceTravelled = _pulseCounter/PULSES_PER_CENTIMETER;
	}
	detachInterrupt(_interruptPin);
}

void updateCounter(){
	_pulseCounter++;
}

void Smartcar::resetCounter(){
	_pulseCounter = 0;
}

void Smartcar::resetDistanceTravelled(){
	_distanceTravelled = 0;
}

void Smartcar::initializeMagnetometer(){} //TO-DO

int Smartcar::getMagnetometerData(){} //TO-DO
