//Implementation of the final review finite state machine (fsm)
//code. It should be compatible with both the PCB and backup boards.
//The full feature set to be implemented is yet to be determined.

//Nothing has been tested.

//libraries
#include <FiniteStateMachine.h>

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
const int motorSpeed = 50;
const int waitTime = 4000;

//flags and global states
//interrupts
volatile bool motorClosed = false;
volatile bool powerPressed = false;
//anything else additional? add below.
bool statusPressed = false;

const byte NUMBER_OF_STATES = 6;

void doTurnedOn() {
  return;
}

//initialize states
State turnedOn = State(doTurnedOn);
State goingHome = State(doGoingHome);
State waiting = State(doWaiting);
State goingForward = State(doGoingForward);
State stayingClosed = State(doStayingClosed);
State poweredOff = State(doPoweredOff);

FSM stateMachine = FSM(turnedOn);     //initialize state machine, start in state: On

void setup() {
  //this will need to be adjusted later
  Serial.begin(9600);
  pinMode(motorPWMPin, OUTPUT);
//  pinMode(motorInterruptPin, OUTPUT);
//  pinMode(switchPollingPin, INPUT);
//  pinMode(motorDirectionPin, OUTPUT);
//  attachInterrupt(digitalPinToInterrupt(motorInterruptPin), reverseMotor, RISING);
}

void loop() {
  //perform main loop checks
  checkPowerPressed();
  checkStatusPressed();
  
  stateMachine.update();
}

//utility functions
void checkPowerPressed() {
  if (powerPressed) {
    if (stateMachine.isInState(poweredOff)) {
      stateMachine.transitionTo(turnedOn);
    }
    else {
      stateMachine.transitionTo(poweredOff);
    }
  }
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

//state machine utility functions
//void doTurnedOn() {
//  return;
//}

void doGoingHome() {
  
}

void doWaiting() {
  
}

void doGoingForward() {
  
}

void doStayingClosed() {
  
}

void doPoweredOff() {
  
}

