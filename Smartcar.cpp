/*
*	Smartcar.h - A simple library for controlling the smartcar
*	by providing an interface to the Adafruit Motor library.
*	Version: 0.5
*	Author: Dimitris Platis (based on the Smartcar project by Team Pegasus)
*/
#include "Smartcar.h"

volatile unsigned long _pulseCounter = 0;


Smartcar::Smartcar() : motorLeft1(UPPER_LEFT_MOTOR_CHANNEL), motorLeft2(LOWER_LEFT_MOTOR_CHANNEL), motorRight1(UPPER_RIGHT_MOTOR_CHANNEL), motorRight2(LOWER_RIGHT_MOTOR_CHANNEL)
{

}

void Smartcar::begin(){
	initializeGyro(GYRO_OFFSET, GYRO_SAMPLING_RATE, GYRO_SENSITIVITY);
	setLeftDirectionAndSpeed(RELEASE, 0);
	setRightDirectionAndSpeed(RELEASE,0);
	setDefaultRotationSpeed(DEFAULT_ROTATION_SPEED);
	setDefaultMotorSpeed(DEFAULT_MOTOR_SPEED);
	setOdometerInterruptPin(ODOMETER_PIN);
	setAutomationMotorSpeed(AUTOMATION_MOTOR_SPEED);
	setAutomationRotationSpeed(AUTOMATION_ROTATION_SPEED);
	delay(1500); //wait to make sure everything has started
}

void Smartcar::goForward(){
	setLeftDirectionAndSpeed(FORWARD, _defaultMotorSpeed);
	setRightDirectionAndSpeed(FORWARD, _defaultMotorSpeed);
}
void Smartcar::goForward(int centimeters){
	setDefaultMotorSpeed(_automationMotorSpeed);
	goForward();
	travelDistance(centimeters);
	stop();
	restoreDefaultMotorSpeed();
}

void Smartcar::goBackward(){
	setLeftDirectionAndSpeed(BACKWARD, _defaultMotorSpeed);
	setRightDirectionAndSpeed(BACKWARD, _defaultMotorSpeed);
}
void Smartcar::goBackward(int centimeters){
	setDefaultMotorSpeed(_automationMotorSpeed);
	goBackward();
	travelDistance(centimeters);
	stop();
	restoreDefaultMotorSpeed();
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
	setLeftDirectionAndSpeed(FORWARD, _defaultRotationSpeed);
	setRightDirectionAndSpeed(BACKWARD, _defaultRotationSpeed);
}
void Smartcar::rotateClockwise(int targetDegrees){
	setDefaultRotationSpeed(_automationRotationSpeed);
	rotateClockwise();
	angularDisplacement(targetDegrees);
	stop();
	restoreDefaultRotationSpeed();
}

void Smartcar::rotateCounterClockwise(){
	setLeftDirectionAndSpeed(BACKWARD, _defaultRotationSpeed);
	setRightDirectionAndSpeed(FORWARD, _defaultRotationSpeed);
}
void Smartcar::rotateCounterClockwise(int targetDegrees){
	setDefaultRotationSpeed(_automationRotationSpeed);
	rotateCounterClockwise();
	angularDisplacement(targetDegrees);
	stop();
	restoreDefaultRotationSpeed();
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

void Smartcar::restoreDefaultMotorSpeed(){
	_defaultMotorSpeed = DEFAULT_MOTOR_SPEED;
}

void Smartcar::setDefaultRotationSpeed(int speed){
	_defaultRotationSpeed = speed;
}

void Smartcar::restoreDefaultRotationSpeed(){
	_defaultRotationSpeed = DEFAULT_ROTATION_SPEED;
}

void Smartcar::setOdometerInterruptPin(short pin){
	_odometerInterruptPin = pin;
}

void Smartcar::setAutomationMotorSpeed(int automationSpeed){
	_automationMotorSpeed = constrain(automationSpeed, MIN_SPEED, MAX_SPEED);
}

void Smartcar::setAutomationRotationSpeed(int rotationSpeed){
	_automationRotationSpeed = constrain(rotationSpeed, MIN_SPEED, MAX_SPEED);
}

void Smartcar::travelDistance(int centimeters){
	attachInterrupt(_odometerInterruptPin, updateCounter, RISING);
	resetCounter();
	resetDistanceTravelled();
	while (centimeters > _distanceTravelled){
		_distanceTravelled = _pulseCounter/PULSES_PER_CENTIMETER;
	}
	detachInterrupt(_odometerInterruptPin);
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


void Smartcar::initializeGyro(int gyroscopeOffset, int gyroscopeSamplingRate,float gyroscopeSensitivity){
	Wire.begin();
	setupL3G4200D(2000); // Configure L3G4200 at 2000 deg/sec. Other options: 250, 500 (NOT suggested, will have to redetermine offset) 
	_gyroscopeOffset = gyroscopeOffset;
	_gyroscopeSamplingRate = gyroscopeSamplingRate;
	_gyroscopeSensitivity = gyroscopeSensitivity;	
}

/* Based on example by Pieter-Jan Van de Maele: http://www.pieter-jan.com/node/7 */
void Smartcar::angularDisplacement(int targetDegrees){
	int gyroValue = 0;
	float angle = 0;
	float gyroRate;
	unsigned long prev = 0;
	unsigned long timeSpan = 0;
	while (abs(angle) < targetDegrees){
		prev = millis();
		delay(_gyroscopeSamplingRate);
		gyroValue = getGyroValues();
		short drift = _gyroscopeOffset - gyroValue;
		if (abs(drift) < GYRO_THRESHOLD){
			gyroRate = 0;
		}else{
			gyroRate = (gyroValue - _gyroscopeOffset) * _gyroscopeSensitivity;
		}
		angle += gyroRate / (1000 / (millis()-prev));
	}
}

/* based on the bildr.org example: http://bildr.org/2011/06/l3g4200d-arduino/ */
int Smartcar::getGyroValues(){
  byte zMSB = readRegister(L3G4200D_Address, 0x2D);
  byte zLSB = readRegister(L3G4200D_Address, 0x2C);
  return ((zMSB << 8) | zLSB);
}

int Smartcar::setupL3G4200D(int scale){
  //From  Jim Lindblom of Sparkfun's code

  // Enable x, y, z and turn off power down:
  writeRegister(L3G4200D_Address, CTRL_REG1, 0b00001111);

  // If you'd like to adjust/use the HPF, you can edit the line below to configure CTRL_REG2:
  writeRegister(L3G4200D_Address, CTRL_REG2, 0b00000000);

  // Configure CTRL_REG3 to generate data ready interrupt on INT2
  // No interrupts used on INT1, if you'd like to configure INT1
  // or INT2 otherwise, consult the datasheet:
  writeRegister(L3G4200D_Address, CTRL_REG3, 0b00001000);

  // CTRL_REG4 controls the full-scale range, among other things:

  if(scale == 250){
    writeRegister(L3G4200D_Address, CTRL_REG4, 0b00000000);
  }else if(scale == 500){
    writeRegister(L3G4200D_Address, CTRL_REG4, 0b00010000);
  }else{
    writeRegister(L3G4200D_Address, CTRL_REG4, 0b00110000);
  }

  // CTRL_REG5 controls high-pass filtering of outputs, use it
  // if you'd like:
  writeRegister(L3G4200D_Address, CTRL_REG5, 0b00000000);
}

void Smartcar::writeRegister(int deviceAddress, byte address, byte val) {
    Wire.beginTransmission(deviceAddress); // start transmission to device 
    Wire.write(address);       // send register address
    Wire.write(val);         // send value to write
    Wire.endTransmission();     // end transmission
}

int Smartcar::readRegister(int deviceAddress, byte address){

    int v;
    Wire.beginTransmission(deviceAddress);
    Wire.write(address); // register to read
    Wire.endTransmission();

    Wire.requestFrom(deviceAddress, 1); // read a byte

    while(!Wire.available()) {
        // waiting
    }

    v = Wire.read();
    return v;
}
