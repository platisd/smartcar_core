#include <AFMotor.h>
#include <Smartcar.h>
#include <Wire.h>
#include <HMC5883L.h>
#include <SoftwareSerial.h>

SoftwareSerial bluetooth(50,51); // RX, TX
// Only pins: 10, 11, 12, 13,  50, 51, 52, 53,  62, 63, 64, 65, 66, 67, 68, 69 will only work for SoftwareSerial on Arduino Mega!
Smartcar bob;

void setup() {
  bluetooth.begin(9600);
  bob.begin();
}

void loop() {
  handleInput();  
}

void handleInput(){
  if (bluetooth.available()){
    char inChar = bluetooth.read();
    switch (inChar) {
    case 'l': //rotate counter-clockwise
      bob.rotateCounterClockwise();
      break;
    case 'r': //rotate clock-wise
      bob.rotateClockwise();
      break;
    case 'f': //go forward
      bob.goForward();
      break;
    case 'b': //go backward
      bob.goBackward();
      break;
    case 'z': //steer back left
      bob.steerBackLeft();
      break;
    case 'x': //steer back right
      bob.steerBackRight();
      break;
    case 'p': //steer front left
      bob.steerFrontLeft();
      break;
    case 'k': //steer front right
      bob.steerFrontRight();
      break;
    default: //if you receive something that you don't know, just stop
      bob.stop();
    }
  }  
}






