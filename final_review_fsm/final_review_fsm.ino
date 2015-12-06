//Implementation of the final review finite state machine (fsm)
//code. It should be compatible with both the PCB and backup boards

//pin constants
const int motorPin = 5;
const int motorInterruptPin = 3;
const int switchPollingPin = 4;
const int directionPin = 9;

//potentially variable parameters
const int motorSpeed = 50;

//flags and global states
volatile bool motorLimitFlag = false;
bool lastLimitSwitchState = false;

void setup() {
  Serial.begin(9600);
  pinMode(motorPin, OUTPUT);
  pinMode(motorInterruptPin, OUTPUT);
  pinMode(switchPollingPin, INPUT);
  pinMode(directionPin, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(motorInterruptPin), reverseMotor, RISING);
}

void loop() {

}

