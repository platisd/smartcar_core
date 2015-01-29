/*
*	Smartcar.h - A simple library for controlling the smartcar
*	by providing an interface to the Adafruit Motor library.
*	Version: 0.4
*	Author: Dimitris Platis (based on the Smartcar project by Team Pegasus)
*/
#include "Smartcar.h"

volatile unsigned short _pulseCounter = 0;

Smartcar::Smartcar() : motorLeft1(UPPER_LEFT_MOTOR_CHANNEL), motorLeft2(LOWER_LEFT_MOTOR_CHANNEL), motorRight1(UPPER_RIGHT_MOTOR_CHANNEL), motorRight2(LOWER_RIGHT_MOTOR_CHANNEL)
{
	setDefaultMotorSpeed(200);
	setInterruptPin(4);
}

void Smartcar::begin(){
	Wire.begin();
	compass.SetScale(1.3);
	compass.SetMeasurementMode(Measurement_Continuous);
	setLeftDirectionAndSpeed(RELEASE, 0);
	setRightDirectionAndSpeed(RELEASE,0);
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
	setLeftDirectionAndSpeed(FORWARD, ROTATION_SPEED);
	setRightDirectionAndSpeed(BACKWARD, ROTATION_SPEED);
}
void Smartcar::rotateClockwise(int targetDegrees){
	rotateClockwise();
	int initialPosition = getMagnetometerDegrees();
	int compensation = 0;
	if(initialPosition - targetDegrees < 0){
		compensation = -360;
	}
	rotateDegrees(targetDegrees, initialPosition, compensation);
	stop();
}


void Smartcar::rotateCounterClockwise(){
	setLeftDirectionAndSpeed(BACKWARD, ROTATION_SPEED);
	setRightDirectionAndSpeed(FORWARD, ROTATION_SPEED);
}
void Smartcar::rotateCounterClockwise(int targetDegrees){
	rotateCounterClockwise();
	int initialPosition = getMagnetometerDegrees();
	int compensation = 0;
	if (initialPosition + targetDegrees > 360){
		compensation = 360;
	}
	rotateDegrees(targetDegrees, initialPosition, compensation);
	stop();
}

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

void Smartcar::rotateDegrees(int targetDegrees, int initialPosition, int compensation){
	targetDegrees = constrain(targetDegrees,1,359);
	int magnetometerDegrees = getMagnetometerDegrees();
	delay(200);
	while ((abs(initialPosition - magnetometerDegrees)< targetDegrees)){
		delay(20);
		magnetometerDegrees = getMagnetometerDegrees();
		if ((compensation > 0) && (magnetometerDegrees<initialPosition)){
			magnetometerDegrees += compensation;
		}
		else if ((compensation < 0) && (magnetometerDegrees>initialPosition)){
			magnetometerDegrees += compensation;
		}
	}
}

/* based on the HMC5883L library's example */
int Smartcar::getMagnetometerDegrees(){
	MagnetometerRaw raw = compass.ReadRawAxis();
	float heading = atan2(raw.YAxis, raw.XAxis);
	float declinationAngle = 98.32/1000; //for Sweden
	heading += declinationAngle;
	if(heading <0) heading += 2*PI;
	if(heading > 2*PI) heading -= 2*PI;
	float headingDegrees = heading * 180/M_PI;
	float adjustedDegrees = 0;
	if (headingDegrees<=150){ //TO-DO fix with a more accurate formula
		adjustedDegrees = headingDegrees/1.55;
	}
	else if (headingDegrees<=240){
		adjustedDegrees = headingDegrees -60;
	}
	else if (headingDegrees<=360){
		adjustedDegrees = (headingDegrees -100)/0.72;
	}
	return adjustedDegrees;  
}
