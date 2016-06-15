/*
  RepRapTester
  This sketch was designed for the RepRapTester made from 3D printed parts, nuts, bolts, 300mm long 51mm square tubing. Find the 3D printed parts on my GitHub page:
  https://github.com/charliegodfrey/RepRapTester

  This Arduino electronics and code performs the following stages:

  1. Drives the stepper motor back to the limit switch - Done
  2. Drives the stepper motor to allow placement of the specimen - Done
  3. Waits for the user to press the Start button - Done
  4. Zeros the load cell - Done
  5. Drives the stepper motor at a set rate (specified in the sketch) whilst printing stress and strain data to the serial terminal - Done
  6. Stops after travelling 30mm (Assumes the specimen has already broken after this movement) - Done


  The circuit:
  Arduino Uno/Nano
  DRV8825
  Stepper motor
  HX711
  Load cell

  Uses the Arduino HX711 library courtesy of bogde: https://github.com/bogde/HX711.git

  Created day month year
  By Charlie Godfrey


*/
#include "HX711.h"
const int stepPin = 2;
const int directionPin = 3;
const int stepperEnablePin = 4;
const int dtPin = A1; //Digital communication pins of the HX711
const int sckPin = A0; //Digital communication pins of the HX711
const int limitPin = 5;
boolean limitState = LOW;
const int startButtonPin = 6;
boolean startState = LOW;
const int strainRate = 60; //Speed of Stepper motor during tensile test in mm per minute
int stepsPermm = 1000;
int totalSteps = stepsPermm * 20
float timeBetweenSteps = ((strainRate/60)/stepsPermm) * 1000000.0; //the time in microseconds between each step of the stepper motor
const float startLocation = 10; // The distance from the limit switch to the position where the specimen can be placed in
int startLocationSteps = startLocation * stepsPermm; // The number of stepper motor steps this equates to

HX711 scale(A1, A0);    // parameter "gain" is ommited; the default value 128 is used by the library

// HX711.DOUT  - pin #A1
// HX711.PD_SCK - pin #A0

void setup() {
  Serial.begin(9600);
  //Move stepper motor in reverse until the microswitch is reached
  digitalWrite(stepperEnablePin, HIGH); //Enable the stpper motor
  digitalWrite(directionPin, HIGH); //Reverse the stepper motor
  do
  {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(250);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(250);
    limitState = digitalRead(limitPin);
  } while (limitState == LOW);

  Serial.println("The carriage has reached the origin");
  delay(200)
  // Drive the stepper motor to the start location so that the specimen can be placed in
  Serial.println("The carriage is driving to the start of the ");
  digitalWrite(directionPin, LOW); //Put the stepper motor into forward mode
  for (int i = 0; i <= startLocationSteps; i++) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(250);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(250);
  }
  
  if (digitalRead(startButtonPin) == HIGH) {
    delay(1000);
    scale.set_scale(2280.f);                      // this value is obtained by calibrating the scale with known weights; see the README for details
    scale.tare(); //Zero the scale
    delay(200);
  }
  int count = 0;
  for (int i = 0; i <= totalSteps; i++) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(timeBetweenSteps / 2);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(timeBetweenSteps / 2);
    count = count + 1;
    if (count == 5){
      Serial.print(i * stepsPermm);
      Serial.print(scale.get_units(), 1);
      count = 0
    }
  }
  
}

void loop() {
  // put your main code here, to run repeatedly:

}
