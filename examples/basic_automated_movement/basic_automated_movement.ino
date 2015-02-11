#include <AFMotor.h>
#include <Smartcar.h>
#include <Wire.h>

Smartcar elsa;

void setup() {
    elsa.begin();
    elsa.goForward(60);
    elsa.rotateClockwise(90);
    elsa.goForward(60);
    elsa.rotateCounterClockwise(90);
    elsa.goBackward(60);
    elsa.rotateCounterClockwise(90);
    elsa.goForward(60);
    elsa.rotateCounterClockwise(270);
}

void loop() {
}
