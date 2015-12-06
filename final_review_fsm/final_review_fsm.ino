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
const int forwardMotorSpeed = 50;
const int reverseMotorSpeed = 128;
const bool forwardDirection = HIGH;
const int waitTime = 4000;
elapsedMillis timeElapsed;

//flags and global states
//interrupts
volatile bool motorClosed = false;
volatile bool powerPressed = false;
//anything else additional? add below.
bool statusPressed = false;

const byte NUMBER_OF_STATES = 6;

void doTurnedOn() {
  // This function was placed abote the initialize states to prevent a function 
  // not defined. Furthremore, we must "extend" the function to prevent calling
  // an FSM object function which does not exist yet.
  if (checkHome()){
    // if home, then wait
    doTurnedOnTransitions(false);
//    stateMachine.transitionTo(waiting); replaced above
  }
  else {
    // if not home, go home
    doTurnedOnTransitions(true);
//    stateMachine.transitionTo(goingHome); replaced above
  }
}

//initialize states
State turnedOn = State(doTurnedOn);
State goingHome = State(doGoingHome);
State waiting = State(doWaiting);
State goingForward = State(doGoingForward);
State stayingClosed = State(doStayingClosed);
State poweredOff = State(doPoweredOff);

FSM stateMachine = FSM(turnedOn);     //initialize state machine, start in state: On

void doTurnedOnTransitions(bool nextState) {
  if (nextState == true) {
    stateMachine.transitionTo(goingHome);
  }
  else {
    stateMachine.transitionTo(waiting);
  }
}

void setup() {
  //this will need to be adjusted later
  Serial.begin(9600);
  pinMode(motorPWMPin, OUTPUT);
//  pinMode(motorInterruptPin, OUTPUT);
//  pinMode(switchPollingPin, INPUT);
//  pinMode(motorDirectionPin, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(motorClosedPin), setMotorClosed, RISING);
//  attachInterrupt(digitalPinToInterrupt(motorClosedPin), setMotorClosed, CHANGE);
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

bool checkHome() {
  if (digitalRead(motorOpenPin) == HIGH) {
    return true;
  }
  else {
    return false;
  }
}

void setMotorClosed() {
  motorClosed = true;
}

//state machine utility functions
void doGoingHome() {
  if (checkHome()) {
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

void doPoweredOff() {
  
}

