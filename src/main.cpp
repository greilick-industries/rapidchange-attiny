// Servo8Bit Example code
// Ilya Brutman

#include <Arduino.h>
#include "Servo8Bit.h"

Servo8Bit myServo, myServo2;  //create a servo object.

const byte rightMotorPin = 1;
const byte leftMotorPin = 0;
const byte motorControlPin = 2;
const byte toggleOverridePin = 3;
bool isOpen = false;
const byte maxAngle = 180;
const byte minAngle = 0;
const int minMicros = 544;
const int maxMicros = 2450;
const byte motorSpeedDelay = 20;

void closeDustCover();
void openDustCover();

bool toggle;
bool toggleOverride;
bool isToggleOverride = false;


void setup()
{
    pinMode(motorControlPin, INPUT_PULLUP);
    pinMode(toggleOverridePin, INPUT_PULLUP);
    myServo.attach(leftMotorPin, minMicros, maxMicros);  //attach the servo to pin PB1
    myServo2.attach(rightMotorPin, minMicros, maxMicros);

    delay(250);
}

void loop() {
  toggleOverride = !digitalRead(toggleOverridePin);
  if (toggleOverride && isToggleOverride && isOpen) {
    isToggleOverride = false;
    closeDustCover();
  } else if (toggleOverride && !isToggleOverride && !isOpen) {
    isToggleOverride = true;
    openDustCover();
  }

  if (isToggleOverride) { return; }

  toggle = digitalRead(motorControlPin);
  if (toggle && !isOpen) {
    openDustCover();
  } else if (!toggle && isOpen) {
    closeDustCover();
  }
}

void openDustCover() {
  for(int x=maxAngle; x >= minAngle; x-=10) {
    myServo.write(x);
    myServo2.write(maxAngle-x);
    delay(motorSpeedDelay);
  }
  isOpen = true;
}

void closeDustCover() {
  for(int x=minAngle; x <= maxAngle; x+=10) {
    myServo.write(x);
    myServo2.write(maxAngle-x);
    delay(motorSpeedDelay);
  }
    isOpen = false;
}
