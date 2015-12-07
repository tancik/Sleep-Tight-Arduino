#include <elapsedMillis.h>
#include <FiniteStateMachine.h>

//Implementation of the final review finite state machine (fsm)
//code. It should be compatible with both the PCB and backup boards.
//The full feature set to be implemented is yet to be determined.

//Nothing has been tested.


//pin constants
//interface switches/buttons
const int powerBtnPin = 2;
const int statusBtnPin = 6;
//motor related pins
const int motorPWMPin = 5;
const int motorClosedPin = 3;
const int motorOpenPin = 4;
const int motorDirectionPin = 9;
//misc.
const int statusLEDPin = 10;

//important global parameters
const int forwardMotorSpeed = 255;
const int reverseMotorSpeed = 255;
const bool forwardDirection = HIGH;
const int waitTime = 4000;
elapsedMillis timeElapsed;

//flags and global states
//interrupts
volatile bool motorClosed = false;
volatile bool powerPressed = false;
//anything else additional? add below.
bool statusPressed = false;

const byte NUMBER_OF_STATES = 7;

void doTurnedOn() {
  // This function was placed abote the initialize states to prevent a function 
  // not defined. Furthremore, we must "extend" the function to prevent calling
  // an FSM object function which does not exist yet.
  doTurnedOnTransition();
}

//initialize states
State turnedOn = State(doTurnedOn);
State goingHome = State(doGoingHome);
State waiting = State(doWaiting);
State goingForward = State(doGoingForward);
State stayingClosed = State(doStayingClosed);
State poweringOff = State(doPoweringOff);
State poweredOff = State(doPoweredOff);

FSM stateMachine = FSM(turnedOn);     //initialize state machine, start in state: On

void doTurnedOnTransition() {
  stateMachine.transitionTo(goingHome);
}

void setup() {
  //this will need to be adjusted later
  Serial.begin(9600);
  pinMode(motorPWMPin, OUTPUT);
//  pinMode(motorInterruptPin, OUTPUT);
//  pinMode(switchPollingPin, INPUT);
//  pinMode(motorDirectionPin, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(motorClosedPin), setMotorClosed, RISING);
  attachInterrupt(digitalPinToInterrupt(powerBtnPin), setPowerPressed, RISING);
}

void loop() {
  //perform main loop checks
  
  checkPowerPressed();
  
  checkStatusPressed();
  
  stateMachine.update();
  // debugging lines
    Serial.print(digitalRead(powerBtnPin));
    Serial.print("\t");
    Serial.print(digitalRead(motorOpenPin));
    Serial.print("\t");
    Serial.print(digitalRead(motorClosedPin));
    Serial.print("\t");
    
    if (stateMachine.isInState(turnedOn)) {Serial.println("turned on");}
    else if (stateMachine.isInState(waiting)) {Serial.println("waiting");}
    else if (stateMachine.isInState(goingHome)) {Serial.println("going home");}
    else if (stateMachine.isInState(stayingClosed)) {Serial.println("staying closed");}
    else if (stateMachine.isInState(poweringOff)) {Serial.println("powering off");}
    else if (stateMachine.isInState(poweredOff)) {Serial.println("powered off");}
    else if (stateMachine.isInState(goingForward)) {Serial.println("going forward");}
}

//utility functions
void checkPowerPressed() {
  Serial.println(powerPressed);
  if (powerPressed) {
//    Serial.println(powerPressed);
    if (stateMachine.isInState(poweredOff)) {
      blinkLED(statusLEDPin, 300, 3);
      stateMachine.transitionTo(turnedOn);
    }
    else {
      stateMachine.transitionTo(poweringOff);
    }
   powerPressed = false;
  }
}

void setPowerPressed() {
  cli(); //disable interrupts
  Serial.println("setPowerPressed");
  //This should be revised if possible. Due to erratic signals, the interrupt
  //is being called during tightening. The poweringOff state is disabled
  //during tightening as a consequence.
  if (!stateMachine.isInState(goingForward) && !stateMachine.isInState(goingHome)) {
    powerPressed = true;
  }
  sei(); //reenable interrupt
}

void checkStatusPressed() {
  if (digitalRead(statusBtnPin) == LOW && statusPressed) {
    digitalWrite(statusLEDPin, LOW);
    statusPressed = false;
  }
  if (digitalRead(statusBtnPin) == HIGH && !stateMachine.isInState(poweredOff)) {
    digitalWrite(statusLEDPin, HIGH);
    statusPressed = true;
  }
}

bool checkHome() {
  if (digitalRead(motorOpenPin) == HIGH) {
    return true;
  }
  else {
    return false;
  }
}

void setMotorClosed() {
  cli(); //disable interrupts
//  analogWrite(motorPWMPin, 0);
//  delay(10);
//  if (digitalRead(motorClosedPin)
  motorClosed = true;
  sei(); //reenable interrupt
}

void blinkLED(int ledPin, int blinkDelay, int numBlinks) {
  /*!
   * Blink the LED when called
   */
   for (int i=0; i < numBlinks; i++) {
    digitalWrite(ledPin, HIGH);
    delay(blinkDelay);
    digitalWrite(ledPin, LOW);
    delay(blinkDelay);
   }
}

//state machine utility functions
void doGoingHome() {
  if (checkHome() && !stateMachine.isInState(waiting)) {
    analogWrite(motorPWMPin, 0);
    timeElapsed = 0;
    stateMachine.transitionTo(waiting);
  }
  else {
    digitalWrite(motorDirectionPin, !forwardDirection);
    analogWrite(motorPWMPin, reverseMotorSpeed);
  }
}

void doWaiting() {
  if (timeElapsed >= waitTime) {
    stateMachine.transitionTo(goingForward);
  }
}

void doGoingForward() {
  if (motorClosed) {
    analogWrite(motorPWMPin, 0);
    stateMachine.transitionTo(stayingClosed);
  }
  else {
    digitalWrite(motorDirectionPin, forwardDirection);
    analogWrite(motorPWMPin, forwardMotorSpeed);
  }
}

void doStayingClosed() {
  
}

void doPoweringOff() {
  if (!checkHome()) {
    digitalWrite(motorDirectionPin, !forwardDirection);
    analogWrite(motorPWMPin, reverseMotorSpeed);
  }
  else {
    analogWrite(motorPWMPin, 0);
    stateMachine.transitionTo(poweredOff);
  }
  if (digitalRead(motorClosedPin) == LOW) {
    motorClosed = false;
  }
}

void doPoweredOff() {
  
}

