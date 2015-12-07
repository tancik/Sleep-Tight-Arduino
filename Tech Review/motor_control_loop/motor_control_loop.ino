#include "elapsedMillis.h"
#include "RunningAverage.h"

elapsedMillis elapsedTime;
RunningAverage myRA(20);

int motorPin = 5;
int directionPin = 8;
int onOffPin = 4; // the pin value needs to be changed
int maxPosition=700;
bool onOffState = false;
bool onOffCheck = false;
//bool direction = true;
int minPosition = 10;
bool motorRunning = false;
bool waiting = false;
int waitTime = 4000;
bool motorIn = false;
int ledPin = 7;


void setup() {
  Serial.begin(9600);
  
  pinMode(motorPin, OUTPUT);
  pinMode(directionPin, OUTPUT);
  pinMode(onOffPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  pinMode(A0, INPUT);
  digitalWrite(directionPin, HIGH);
  analogWrite(motorPin,0);
}

void loop() {
  int actuatorPos = analogRead(A0); // get the actuator pot value
  
  // stop the motor if it has extended too far
  if(motorRunning && (actuatorPos > maxPosition) && !motorIn){    
    motorRunning = stopMotor(motorPin);
    waiting = false;
    Serial.println("If 1");
  }
  // stop the motor if it has contracted too much
  if (motorRunning && (actuatorPos < minPosition) && motorIn){
    motorRunning = stopMotor(motorPin);
    Serial.println("If 2");
  }
  // check to see if the on-off switch has been flipped
  if (onOffState == digitalRead(onOffPin)) {
    onOffState = !digitalRead(onOffPin);
    waiting = false;
    Serial.println("If 3");
    if (onOffState && (actuatorPos > minPosition)){
      // wait if the device was turned on and the actuator arm is
      // extended
      controlLED(ledPin);
      waiting = true;
      elapsedTime = 0; // initialize the timer to 0
      Serial.println("If 3 1");
    }
    else if(!onOffState && (actuatorPos < maxPosition)){
      // extend the actuator arm if the device is turned off
      digitalWrite(directionPin, HIGH);
      Serial.println(digitalRead(directionPin));
      motorRunning = startMotor(motorPin, 255);
      motorIn = false;    
    }
  }
  if (waiting && (elapsedTime > waitTime)){
    Serial.println("If 4");
    // if we have met the tightening criteria, start tightening
    waiting=false;
    digitalWrite(directionPin, LOW);
    motorRunning = startMotor(motorPin, 122);
    motorIn = true;
  }

}

bool startMotor(int motorPin, int motorSpeed) {
  /*!  
   * Start the motor ata defined speed and change the motorRunning flag to true
   * 
   * Keywords:
   *  int motorPin: Corresponding Arduino pin
   *  int motorSpeed: Arduino PWM value between 0 and 255
   * Returns:
   *  bool = true: flag indicating that the motor is running
   */
   analogWrite(motorPin, motorSpeed);
   waiting = false;
   return true;
}

bool stopMotor(int motorPin) {
  /*!  
   * Stop the motor by setting the writing 0 to the pin
   * 
   * Keywords:
   *  int motorPin: Corresponding Arduino pin
   * Returns:
   *  bool = false: flag indicating that the motor is stopped
   */
   analogWrite(motorPin, 0);
   return false;
}

void controlLED(int ledPin) {
  /*!
   * Blink the LED when called
   */
   for (int i=0; i < 3; i++) {
    digitalWrite(ledPin, HIGH);
    delay(1000);
    digitalWrite(ledPin, LOW);
    delay(1000);
   }
}


