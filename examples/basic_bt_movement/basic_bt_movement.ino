#include <AFMotor.h>
#include <Smartcar.h>
#include <Wire.h>
#include <SoftwareSerial.h>


SoftwareSerial bluetooth(50,51); // RX, TX
// Only pins: 10, 11, 12, 13,  50, 51, 52, 53,  62, 63, 64, 65, 66, 67, 68, 69 will only work for SoftwareSerial on Arduino Mega!
Smartcar bob;

void setup() {
  bob.begin();
  bluetooth.begin(9600);
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
    case 'z': //turn back left
      bob.turnBackLeft();
      break;
    case 'x': //turn back right
      bob.turnBackRight();
      break;
    case 'p': //turn front left
      bob.turnFrontLeft();
      break;
    case 'k': //turn front right
      bob.turnFrontRight();
      break;
    default: //if you receive something that you don't know, just stop
      bob.stop();
    }
  }  
}
